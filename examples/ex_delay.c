#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_delay *delay;
    ut_osc *osc;
    ut_metro *met;
    ut_tenv *tenv;
    ut_ftbl *ft;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, delay = 0, met = 0, tenv = 0;
    ut_metro_compute(ut, ud->met, NULL, &met);
    ut_tenv_compute(ut, ud->tenv, &met, &tenv);
    if(met) {
        ud->osc->freq = 100 + rand() % 500;
    }
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    osc *= tenv;
    ut_delay_compute(ut, ud->delay, &osc, &delay);
    ut->out[0] = osc + delay;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_delay_create(&ud.delay);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_metro_create(&ud.met);
    ut_tenv_create(&ud.tenv);

    ut_delay_init(ut, ud.delay, 0.75 * 0.5);
    ud.delay->feedback = 0.5;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->amp = 0.5;
    ut_metro_init(ut, ud.met);
    ud.met->freq = 1;
    ut_tenv_init(ut, ud.tenv);
    ud.tenv->atk = 0.005;
    ud.tenv->hold = 0.1;
    ud.tenv->rel =  0.1;


    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_delay_destroy(&ud.delay);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_metro_destroy(&ud.met);
    ut_tenv_destroy(&ud.tenv);

    ut_destroy(&ut);
    return 0;
}
