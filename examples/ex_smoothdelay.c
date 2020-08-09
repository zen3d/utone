#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_smoothdelay *smoothdelay;
    ut_osc *osc;
    ut_ftbl *ft; 
    ut_diskin *diskin;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, smoothdelay = 0, diskin = 0;
    ut_diskin_compute(ut, ud->diskin, NULL, &diskin);
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    osc = 0.1 + (0.5 * (1 + osc)) * 0.8;
    ud->smoothdelay->del = osc;
    ut_smoothdelay_compute(ut, ud->smoothdelay, &diskin, &smoothdelay);
    ut->out[0] = diskin + smoothdelay;
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 1234567);

    ut_smoothdelay_create(&ud.smoothdelay);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_diskin_create(&ud.diskin);

    ut_smoothdelay_init(ut, ud.smoothdelay, 1.0, 1024);
    ud.smoothdelay->feedback = 0.5;
    ud.smoothdelay->del = 0.1;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->freq = 0.2;
    ud.osc->amp = 1.0;
    ut_diskin_init(ut, ud.diskin, "oneart.wav");

    ut->len = 44100 * 10;
    ut_process(ut, &ud, process);

    ut_smoothdelay_destroy(&ud.smoothdelay);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_diskin_destroy(&ud.diskin);

    ut_destroy(&ut);
    return 0;
}
