/*
 * When rendered, this will generate two files: 00_test.wav and 01_test.wav
 *
 * These two files can be interleaved together to a single file using sox:
 *
 * sox -M 00_test.wav 01_test.wav -c 2 out.wav
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_pan2 *pan2;
    ut_osc *osc;
    ut_osc *lfo;
    ut_ftbl *ft; 
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, outL = 0, outR = 0, lfo = 0;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut_osc_compute(ut, ud->lfo, NULL, &lfo);
    ud->pan2->pan = lfo;
    ut_pan2_compute(ut, ud->pan2, &osc, &outL, &outR);
    ut_out(ut, 0, outL);
    ut_out(ut, 1, outR);
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_createn(&ut, 2);

    ut_pan2_create(&ud.pan2);
    ut_osc_create(&ud.osc);
    ut_osc_create(&ud.lfo);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_pan2_init(ut, ud.pan2);
    ud.pan2->type = 2;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ut_osc_init(ut, ud.lfo, ud.ft, 0);
    ud.lfo->amp = 1;
    ud.lfo->freq = 1;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_pan2_destroy(&ud.pan2);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_osc_destroy(&ud.lfo);

    ut_destroy(&ut);
    return 0;
}
