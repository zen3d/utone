#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_osc *osc;
    ut_ftbl *ft;
    ut_metro *met;
    ut_tenv *tenv;
    UTFLOAT freq;
} UserData;

void write_osc(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT trig = 0;
    UTFLOAT env = 0;
    UTFLOAT osc = 0;
    ut_metro_compute(ut, ud->met, NULL, &trig);
    if(trig) ud->osc->freq = 500 + ut_rand(ut) % 2000;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut_tenv_compute(ut, ud->tenv, &trig, &env);

    ut->out[0] = osc * env;
}

int main() {
    UserData ud;
    UTFLOAT *freqp = &ud.freq;
    ud.freq = 400;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 123456);

    ut_tenv_create(&ud.tenv);
    ut_metro_create(&ud.met);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_osc_create(&ud.osc);

    ut_tenv_init(ut, ud.tenv);
    ud.tenv->atk = 0.03;
    ud.tenv->hold = 0.1;
    ud.tenv->rel = 0.1;
    ut_metro_init(ut, ud.met);
    ud.met->freq = 3;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->freq = *freqp;
    ut->len = 44100 * 5;
    ut_process(ut, &ud, write_osc);

    ut_tenv_destroy(&ud.tenv);
    ut_metro_destroy(&ud.met);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_destroy(&ut);
    return 0;
}
