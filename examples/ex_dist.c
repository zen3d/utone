#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_fosc *osc;
    ut_ftbl *ft;
    ut_dist *ds;
    ut_osc *lfo;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, lfo = 0;
    ut_osc_compute(ut, ud->lfo, NULL, &lfo);
    lfo = 7 * (0.5 * (lfo + 1));
    ud->osc->indx = lfo;
    ut_fosc_compute(ut, ud->osc, NULL, &osc);
    ut_dist_compute(ut, ud->ds, &osc, &ut->out[0]);
}

int main() {
    srand(time(NULL));
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_fosc_create(&ud.osc);
    ut_dist_create(&ud.ds);
    ut_osc_create(&ud.lfo);

    ut_gen_sine(ut, ud.ft);
    ut_fosc_init(ut, ud.osc, ud.ft);
    ud.osc->freq = 60;
    ut_dist_init(ut, ud.ds);
    ud.ds->pregain = 10;
    ut_osc_init(ut, ud.lfo, ud.ft, 0);
    ud.lfo->freq = 0.5;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_ftbl_destroy(&ud.ft);
    ut_fosc_destroy(&ud.osc);
    ut_dist_destroy(&ud.ds);
    ut_osc_destroy(&ud.lfo);
    ut_destroy(&ut);
    return 0;
}
