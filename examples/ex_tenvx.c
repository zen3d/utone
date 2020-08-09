#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_osc *osc;
    ut_ftbl *ft;
    ut_metro *met;
    ut_tenvx *tenvx;
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
    ut_tenvx_compute(ut, ud->tenvx, &trig, &env);

    ut->out[0] = osc * env;
}

int main() {
    UserData ud;
    UTFLOAT *freqp = &ud.freq;
    ud.freq = 400;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 123456);

    ut_tenvx_create(&ud.tenvx);
    ut_metro_create(&ud.met);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_osc_create(&ud.osc);

    ut_tenvx_init(ut, ud.tenvx);
    ud.tenvx->atk = 0.03;
    ud.tenvx->hold = 0.1;
    ud.tenvx->rel = 0.1;
    ut_metro_init(ut, ud.met);
    ud.met->freq = 3;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->amp = 0.5;
    ud.osc->freq = *freqp;
    ut->len = 44100 * 5;
    ut_process(ut, &ud, write_osc);

    ut_tenvx_destroy(&ud.tenvx);
    ut_metro_destroy(&ud.met);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_destroy(&ut);
    return 0;
}
