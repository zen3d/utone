
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_metro *met;
    ut_trand *trand;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, trand = 0, met = 0;
    ut_metro_compute(ut, ud->met, NULL, &met);
    ut_trand_compute(ut, ud->trand, &met, &trand);
    ud->osc->freq = trand;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut->out[0] = osc;
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 1234567);

    ut_metro_create(&ud.met);
    ut_trand_create(&ud.trand);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_metro_init(ut, ud.met);
    ud.met->freq = 20;
    ut_trand_init(ut, ud.trand);
    ud.trand->min = 40;
    ud.trand->max = 1000;

    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_trand_destroy(&ud.trand);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_metro_destroy(&ud.met);

    ut_destroy(&ut);
    return 0;
}
