#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <utone.h>
#define NUMLINE 3


typedef struct {
    ut_mode *mode[4];
    UTFLOAT *mfreq[4];
    UTFLOAT *Q[4];
    UTFLOAT amp;
    UTFLOAT *freq;
    UTFLOAT lfreq;
} modal;

typedef struct {
    ut_dust *dust;
    ut_osc *osc;
    ut_tenv *env;
    ut_tevent *retrig;
    UTFLOAT amp;
} chord_grain;

typedef struct {
    ut_ftbl *sine;
    ut_ftbl *notes;
    UTFLOAT ampmax;
    chord_grain *grains;
} chord_cloud;

int modal_create(modal **md)
{
    *md = malloc(sizeof(modal));
    return UT_OK;
}

int modal_init(ut_data *ut, modal *md)
{
    int i;
    md->amp = 0.45;

    for(i = 0; i < 4; i++) {
        ut_mode_create(&md->mode[i]);
        ut_mode_init(ut, md->mode[i]);
        md->mfreq[i] = &md->mode[i]->freq;
        md->Q[i] = &md->mode[i]->q;
    }

    *md->mfreq[0] = 1000;
    *md->mfreq[1] = 3000;
    *md->Q[0] = 12;
    *md->Q[1] = 8;

    *md->mfreq[2] = 440;
    *md->mfreq[3] = *md->mfreq[2] * 2.01081;
    *md->Q[2] = 500;
    *md->Q[3] = 420;

    md->freq = md->mfreq[2];
    md->lfreq = *md->freq;
    return UT_OK;
}

int modal_compute(ut_data *ut, modal *md, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT exc1, exc2, exc;
    UTFLOAT res1, res2, res;

    if(*md->freq != md->lfreq) {
        *md->mfreq[3] = *md->freq * 2.01081;
        md->lfreq = *md->freq;
    }

    ut_mode_compute(ut, md->mode[0], in, &exc1);
    ut_mode_compute(ut, md->mode[1], in, &exc2);
    exc = (exc1 + exc2) * 0.5;

    if(exc > md->amp) {
        exc = md->amp;
    } else if (exc < 0 ) {
        exc = 0;
    }

    ut_mode_compute(ut, md->mode[2], &exc, &res1);
    ut_mode_compute(ut, md->mode[3], &exc, &res2);
    res = (res1 + res2) * 0.5;


    *out = (exc + res) * md->amp;

    return UT_OK;
}

int modal_destroy(modal **md)
{
    int i;
    modal *mdp = *md;
    for(i = 0; i < 4; i++) {
        ut_mode_destroy(&mdp->mode[i]);
    }

    free(*md);
    return UT_OK;
}

static void cloud_compute(void *ud, UTFLOAT *out) {
    chord_cloud *grain = ud;
}

static void cloud_reinit(void *ud) {
    chord_grain *grain = ud;
    int rval = rand();
/*
    Figure out why this clicks
    grain->amp = 0.8 + fabs(0.2 * (UTFLOAT) (1.0 * rval / RAND_MAX));
*/
}


int chord_cloud_create(chord_cloud **cc)
{
    *cc = malloc(sizeof(chord_cloud));
    return UT_OK;
}

int chord_cloud_init(ut_data *ut, chord_cloud *cc, char *notes, UTFLOAT amp)
{
    int i;
    ut_osc *tmposc;
    ut_dust *tmpdust;
    ut_tenv *tmpenv;
    ut_tevent *tmpretrig;

    ut_ftbl_create(ut, &cc->sine, 4096);
    ut_gen_sinesum(ut, cc->sine, "1 0.5 0.3 0.25, 0.1625");
    ut_ftbl_create(ut, &cc->notes, 1);
    ut_gen_vals(ut, cc->notes, notes);
    cc->ampmax= amp;

    cc->grains= malloc(cc->notes->size * sizeof(chord_grain));

    for(i = 0; i < cc->notes->size; i++) {
        chord_grain *grain = &cc->grains[i];
        ut_osc_create(&grain->osc);
        ut_tenv_create(&grain->env);
        ut_dust_create(&grain->dust);
        ut_tevent_create(&grain->retrig);

        tmposc = grain->osc;
        tmpenv = grain->env;
        tmpdust = grain->dust;
        tmpretrig = grain->retrig;

        ut_dust_init(ut, tmpdust);
        tmpdust->amp = 1;
        tmpdust->density = 8;
        ut_osc_init(ut, tmposc, cc->sine, 0);
        tmposc->freq = ut_midi2cps(cc->notes->tbl[i]);
        tmposc->amp = 1.0;
        grain->amp = 1.0;
        ut_tenv_init(ut, tmpenv);
        tmpenv->atk = 0.01;
        tmpenv->hold = 0;
        tmpenv->rel =  0.03;

        ut_tevent_init(ut, tmpretrig, cloud_reinit, cloud_compute, grain);
    }

    return UT_OK;
}

int chord_cloud_compute(ut_data *ut, chord_cloud *cc, UTFLOAT *in, UTFLOAT *out)
{
    int i;
    UTFLOAT dust = 0, osc = 0, env = 0, tmp = 0, dummy;
    for(i = 0; i < cc->notes->size; i++) {
        chord_grain *grain = &cc->grains[i];
        ut_dust_compute(ut, grain->dust, NULL, &dust);
        ut_tenv_compute(ut, grain->env, &dust, &env);
        ut_osc_compute(ut, grain->osc, NULL, &osc);
        ut_tevent_compute(ut, grain->retrig, &dust, &dummy);
        tmp += osc * env * cc->ampmax * grain->amp;
    }
    *out = tmp;
    return UT_OK;
}

int chord_cloud_destroy(chord_cloud **cc)
{
    int i;
    chord_cloud *ccp = *cc;
    ut_dust **tmpdust;
    ut_ftbl_destroy(&ccp->sine);

    for(i = 0; i < ccp->notes->size; i++ ) {
        ut_dust_destroy(&ccp->grains[i].dust);
        ut_osc_destroy(&ccp->grains[i].osc);
        ut_tenv_destroy(&ccp->grains[i].env);
        ut_tevent_destroy(&ccp->grains[i].retrig);
    }
    free(ccp->grains);
    ut_ftbl_destroy(&ccp->notes);
    free(*cc);
    return UT_OK;
}


typedef struct {
    chord_cloud *cc;
    ut_randi *randi;
} CloudLine;

typedef struct {
    CloudLine line[NUMLINE];
    ut_revsc *rev;
    ut_metro *clk;
    ut_count *meter;
    ut_drip *drip;
    ut_vdelay *del;
    UTFLOAT pdel;
    ut_tenv *master;
    modal *mod;
    ut_ftbl *notes;
    ut_tseq *seq;
    ut_maygate *mg;
    ut_progress *prog;
} UserData;

void process(ut_data *ut, void *udata)
{
    UserData *ud = udata;
    int i;
    UTFLOAT line = 0, cloud = 0, tmp = 0, revin = 0, rev = 0, dummy, drip = 0;
    UTFLOAT count = 0;
    UTFLOAT bar = 0, clk = 0, delIn = 0, delOut = 0;
    UTFLOAT mode = 0;

    for(i = 0; i < NUMLINE; i++) {
        ut_randi_compute(ut, ud->line[i].randi, NULL, &line);
        chord_cloud_compute(ut, ud->line[i].cc, NULL, &cloud);
        tmp += cloud * line;
    }
    revin += tmp * 0.5;
    ut_metro_compute(ut, ud->clk, NULL, &clk);
    ut_count_compute(ut, ud->meter, &clk, &count);
    bar = (count == 0 && clk);
    ut_drip_compute(ut, ud->drip, &bar, &drip);
    drip *= 0.5;
    revin += drip * 0.1;

    if(ut->pos > 44100 * 3) {
        UTFLOAT mg = 0, nn = 0;
        ut_maygate_compute(ut, ud->mg, &clk, &mg);
        ut_tseq_compute(ut, ud->seq, &mg, &nn);
        *ud->mod->freq = ut_midi2cps(nn + 12);
        modal_compute(ut, ud->mod, &mg, &mode);
        mode *= 0.3;
        revin += mode * 0.8;
        delIn += mode * 0.5;
    }

    delIn += drip * 0.1 + ud->pdel * 0.6;
    ut_vdelay_compute(ut, ud->del, &delIn, &delOut);
    ud->pdel = delOut;
    revin += delOut * 0.1;


    ut_revsc_compute(ut, ud->rev, &revin, &revin, &rev, &dummy);
    ut->out[0] = tmp * 0.2 + rev * 0.6 + drip * 0.1 + delOut * 0.5 + mode;

    /* Master fader */
    UTFLOAT mtick = (ut->pos == 0) ? 1.0 : 0.0;
    UTFLOAT fader = 0;
    ut_tenv_compute(ut, ud->master, &mtick, &fader);
    ut->out[0] *= fader;
    ut_progress_compute(ut, ud->prog, NULL, NULL);

}

UTFLOAT randf(UTFLOAT max) {
    UTFLOAT num = (UTFLOAT) rand() / (UTFLOAT) (RAND_MAX / max);
    return num;
}

int main()
{
    srand(time(NULL));
    int i;
    UserData ud;
    ud.pdel = 0;
    ut_data *ut;
    ut_create(&ut);
    ut->len = 44100 * 40;
    char *notes[] = {
        "62 69 78",
        "55 62 69 71",
        "43 50"
    };


    for(i = 0; i < NUMLINE; i++) {
        ut_randi_create(&ud.line[i].randi);
        chord_cloud_create(&ud.line[i].cc);
        chord_cloud_init(ut, ud.line[i].cc, notes[i], 0.1);
        ut_randi_init(ut, ud.line[i].randi);
        ud.line[i].randi->cps = 0.1 + randf(1.5);
    }
    ut_revsc_create(&ud.rev);
    ut_revsc_init(ut, ud.rev);
    ud.rev->feedback = 0.95;
    ut_metro_create(&ud.clk);
    ut_metro_init(ut, ud.clk);
    ud.clk->freq = 86.0 / 60.0;
    ut_count_create(&ud.meter);
    ut_count_init(ut, ud.meter);
    ud.meter->count = 5;
    ut_drip_create(&ud.drip);
    ut_drip_init(ut, ud.drip, 0.01);
    ut_vdelay_create(&ud.del);
    /* give some headroom for the delay */
    ut_vdelay_init(ut, ud.del, 0.4);
    ud.del->del = 0.3;

    ut_tenv_create(&ud.master);
    ut_tenv_init(ut, ud.master);
    ud.master->atk = 0;
    ud.master->hold = 30;
    ud.master->rel =  10;


    ut_progress_create(&ud.prog);
    ut_progress_init(ut, ud.prog);

    modal_create(&ud.mod);
    modal_init(ut, ud.mod);
    ut_ftbl_create(ut, &ud.notes, 1);
    ut_gen_vals(ut, ud.notes, "62 64 59 57");
    ut_tseq_create(&ud.seq);
    ut_tseq_init(ut, ud.seq, ud.notes);
    ut_maygate_create(&ud.mg);
    ut_maygate_init(ut, ud.mg);
    ud.mg->prob = 0.3;
    ud.mg->mode = 1;
    ut_process(ut, &ud, process);

    for(i = 0; i < NUMLINE; i++) {
        ut_randi_destroy(&ud.line[i].randi);
        chord_cloud_destroy(&ud.line[i].cc);
    }


    ut_drip_destroy(&ud.drip);
    ut_revsc_destroy(&ud.rev);
    ut_metro_destroy(&ud.clk);
    ut_count_destroy(&ud.meter);
    ut_vdelay_destroy(&ud.del);
    ut_tenv_destroy(&ud.master);
    modal_destroy(&ud.mod);
    ut_ftbl_destroy(&ud.notes);
    ut_tseq_destroy(&ud.seq);
    ut_maygate_destroy(&ud.mg);
    ut_progress_destroy(&ud.prog);

    ut_destroy(&ut);
    return 0;
}
