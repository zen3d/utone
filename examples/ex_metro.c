#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_osc *osc;
    ut_ftbl *ft;
    ut_tenv *tenv;
    ut_metro *met;
    ut_randi *rand;
    UTFLOAT freq;
} UserData;

void write_osc(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, trig = 0, tenv = 0;
    ut_randi_compute(ut, ud->rand, NULL, &ud->met->freq);
    ut_metro_compute(ut, ud->met, NULL, &trig);
    ut_tenv_compute(ut, ud->tenv, &trig, &tenv);
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut->out[0] = tenv * osc;
}

int main() {
    UserData ud;
    UTFLOAT *freqp = &ud.freq;
    ud.freq = 400;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 12345);

    ut_randi_create(&ud.rand);
    ut_metro_create(&ud.met);
    ut_tenv_create(&ud.tenv);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_osc_create(&ud.osc);

    ut_randi_init(ut, ud.rand);
    ud.rand->min = 2.0;
    ud.rand->max= 15.0;
    ut_metro_init(ut, ud.met);
    ut_tenv_init(ut, ud.tenv);
    ud.tenv->atk = 0.005;
    ud.tenv->hold = 0.01;
    ud.tenv->rel = 0.003;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->freq = *freqp;
    ut->len = 44100 * 5;
    ut_process(ut, &ud, write_osc);

    ut_randi_destroy(&ud.rand);
    ut_metro_destroy(&ud.met);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_tenv_destroy(&ud.tenv);
    ut_destroy(&ut);
    return 0;
}
