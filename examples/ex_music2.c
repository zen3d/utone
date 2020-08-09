#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_ftbl *ft, *delta;
    ut_dtrig *dt;
    ut_tevent *te;
    uint32_t pos;
} samp_data;

typedef struct {
    UTFLOAT tempo;
    ut_count *cnt;
    ut_ftbl *reps;
    ut_tseq *rpick;
    ut_metro *clk, *dblclk;
    ut_reverse *rvs;
    ut_maygate *rthrow, *rgate, *rvs_switch;
    ut_revsc *rev;
    ut_rpt *rpt;
    samp_data snare, kick, hh;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT dry;
    UTFLOAT kick, snare, hh, clk, dblclk, bar, dtrig, count;
    UTFLOAT revin, revout, rthrow, rgate, rpt, rvs, rvs_switch, foo;
    UTFLOAT reps;
    ut_metro_compute(ut, ud->clk, NULL, &clk);
    ut_metro_compute(ut, ud->dblclk, NULL, &dblclk);
    ut_count_compute(ut, ud->cnt, &clk, &count);
    bar = (count == 0 && clk);
    ut_dtrig_compute(ut, ud->snare.dt, &bar, &dtrig);
    ut_tevent_compute(ut, ud->snare.te, &dtrig, &snare);

    ut_maygate_compute(ut, ud->rthrow, &dtrig, &rthrow);
    revin = snare * rthrow;
    ut_revsc_compute(ut, ud->rev, &revin, &revin, &revout, &foo);

    ut_dtrig_compute(ut, ud->kick.dt, &bar, &dtrig);
    ut_tevent_compute(ut, ud->kick.te, &dtrig, &kick);
    ut_dtrig_compute(ut, ud->hh.dt, &bar, &dtrig);
    ut_tevent_compute(ut, ud->hh.te, &dtrig, &hh);

    dry = snare + kick + hh * 0.5 + revout * 0.1;
    ut_maygate_compute(ut, ud->rgate, &dblclk, &rgate);
    ut_tseq_compute(ut, ud->rpick, &dblclk, &reps);

    ut_rpt_compute(ut, ud->rpt, &rgate, &dry, &rpt);
    ut_reverse_compute(ut, ud->rvs, &rpt, &rvs);
    ut_maygate_compute(ut, ud->rvs_switch, &clk, &rvs_switch);

    ut->out[0] = (rvs_switch) ? rvs : rpt;
}

void samp_reinit(void *ud) {
    samp_data *sd = ud;
    sd->pos = 0;
}

void samp_compute(void *ud, UTFLOAT *out) {
    samp_data *sd = ud;
    if(sd->pos < sd->ft->size){
        *out = sd->ft->tbl[sd->pos];
        sd->pos++;
    } else {
        *out = 0;
    }
}
void samp_create(ut_data *ut, samp_data *sd,
    size_t size, char *file, char *dtrig, UTFLOAT tempo, UTFLOAT delay) {
    int i;
    UTFLOAT tscale = 60.0 / tempo;
    ut_ftbl_create(ut, &sd->delta, 1);
    ut_gen_vals(ut, sd->delta, dtrig);
    ut_dtrig_create(&sd->dt);
    for(i = 0; i < sd->delta->size; i++){
        sd->delta->tbl[i] *= tscale;
    }
    ut_dtrig_init(ut, sd->dt, sd->delta);

    sd->dt->delay = delay * tscale;

    ut_ftbl_create(ut, &sd->ft, 5574);
    ut_gen_file(ut, sd->ft, file);

    ut_tevent_create(&sd->te);
    ut_tevent_init(ut, sd->te, samp_reinit, samp_compute, sd);

    sd->pos = 0;
}

void samp_destroy(samp_data *sd){
    ut_tevent_destroy(&sd->te);
    ut_ftbl_destroy(&sd->ft);
    ut_ftbl_destroy(&sd->delta);
    ut_dtrig_destroy(&sd->dt);
}


int main() {
    srand(time(NULL));
    ut_data *ut;
    UserData ud;
    ut_create(&ut);

    UTFLOAT tempo = 144;
    ud.tempo = tempo;

    /* Create */
    ut_count_create(&ud.cnt);
    ut_metro_create(&ud.clk);
    ut_metro_create(&ud.dblclk);
    samp_create(ut, &ud.snare, 5574, "snare.wav", "2 0.75 0.25", tempo, 1);
    samp_create(ut, &ud.kick, 7385, "kick.wav", "0.75 1.25 1 1", tempo, 0);
    samp_create(ut, &ud.hh, 4507, "hh.wav",
            "0.5 0.25 0.5 0.5 0.25 0.5 0.25 0.5 0.5 0.25",
            tempo, 0);
    ut_revsc_create(&ud.rev);
    ut_maygate_create(&ud.rthrow);
    ut_maygate_create(&ud.rgate);
    ut_rpt_create(&ud.rpt);
    ut_ftbl_create(ut, &ud.reps, 1);
    ut_tseq_create(&ud.rpick);
    ut_gen_vals(ut, ud.reps, "4 8 16 6");
    ut_tseq_init(ut, ud.rpick, ud.reps);
    ud.rpick->shuf = 1.0;
    ut_reverse_create(&ud.rvs);
    ut_maygate_create(&ud.rvs_switch);

    /* Init */
    ut->len = 44100 * (60.0 / tempo) * 32;
    ut_count_init(ut, ud.cnt);
    ud.cnt->count = 4;
    ut_metro_init(ut, ud.clk);
    ud.clk->freq = tempo / 60.0;
    ut_metro_init(ut, ud.dblclk);
    ud.dblclk->freq = tempo * 2 / 60.0;
    ut_revsc_init(ut, ud.rev);
    ud.rev->feedback = 0.9;
    ud.rev->lpfreq = 10000;
    ut_maygate_init(ut, ud.rthrow);
    ud.rthrow->prob = 0.5;
    ut_rpt_init(ut, ud.rpt, 1.0);
    //ut_rpt_set(ud.rpt, tempo, 8, 4);
    ud.rpt->bpm = tempo;
    ud.rpt->div = 8;
    ud.rpt->reps = 4;
    ut_maygate_init(ut, ud.rgate);
    ud.rgate->prob = 0.18;
    ud.rgate->mode = 1.0;
    ut_reverse_init(ut, ud.rvs, 60.0 / tempo);
    ut_maygate_init(ut, ud.rvs_switch);
    ud.rvs_switch->prob = 0.1;

    /* Process */
    ut_process(ut, &ud, process);

    /* Destroy */
    samp_destroy(&ud.snare);
    samp_destroy(&ud.kick);
    samp_destroy(&ud.hh);
    ut_revsc_destroy(&ud.rev);
    ut_maygate_destroy(&ud.rthrow);
    ut_maygate_destroy(&ud.rgate);
    ut_maygate_destroy(&ud.rvs_switch);
    ut_count_destroy(&ud.cnt);
    ut_metro_destroy(&ud.clk);
    ut_metro_destroy(&ud.dblclk);
    ut_rpt_destroy(&ud.rpt);
    ut_ftbl_destroy(&ud.reps);
    ut_tseq_destroy(&ud.rpick);
    ut_reverse_destroy(&ud.rvs);

    ut_destroy(&ut);
    return 0;
}
