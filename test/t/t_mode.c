#include <stdlib.h>
#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_mode *mode[4];
    UTFLOAT *mfreq[4];
    UTFLOAT *Q[4];
    UTFLOAT amp;
    UTFLOAT *freq;
    UTFLOAT lfreq;
} modal;

typedef struct {
    modal *mod;
    ut_metro *met;
    ut_ftbl *notes;
    ut_tseq *seq;
} UserData;

static int modal_create(modal **md)
{
    *md = malloc(sizeof(modal));
    return UT_OK;
}

static int modal_init(ut_data *ut, modal *md)
{
    int i;
    md->amp = 0.5;


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

static int modal_compute(ut_data *ut, modal *md, UTFLOAT *in, UTFLOAT *out)
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

static int modal_destroy(modal **md)
{
    int i;
    modal *mdp = *md;
    for(i = 0; i < 4; i++) {
        ut_mode_destroy(&mdp->mode[i]);
    }

    free(*md);
    return UT_OK;
}

int t_mode(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UserData ud;
    UTFLOAT met = 0, mod = 0, nn;

    modal_create(&ud.mod);
    modal_init(ut, ud.mod);

    ut_metro_create(&ud.met);
    ut_metro_init(ut, ud.met);
    ud.met->freq = 3.0;

    ut_ftbl_create(ut, &ud.notes, 1);
    ut_gen_vals(ut, ud.notes, "60 67 62 69 76");

    ut_tseq_create(&ud.seq);
    ut_tseq_init(ut, ud.seq, ud.notes);

    for(n = 0; n < tst->size; n++) {
        met = 0; 
        mod = 0; 
        nn = 0;
        ut_metro_compute(ut, ud.met, NULL, &met);
        ut_tseq_compute(ut, ud.seq, &met, &nn);
        *ud.mod->freq = ut_midi2cps(nn);
        modal_compute(ut, ud.mod, &met, &mod);
        ut->out[0] = mod;
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);
    
    modal_destroy(&ud.mod);
    ut_metro_destroy(&ud.met);
    ut_ftbl_destroy(&ud.notes);
    ut_tseq_destroy(&ud.seq);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
