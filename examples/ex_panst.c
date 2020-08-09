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
    ut_panst *panst;
    ut_osc *osc;
    ut_osc *lfo;
    ut_ftbl *ft;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, outL = 0, outR = 0, lfo = 0;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut_osc_compute(ut, ud->lfo, NULL, &lfo);
    ud->panst->pan = lfo;

    ut_panst_compute(ut, ud->panst, &osc, &osc, &outL, &outR);
    ut_out(ut, 0, outL);
    ut_out(ut, 1, outR);
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_createn(&ut, 2);

    ut_panst_create(&ud.panst);
    ut_osc_create(&ud.osc);
    ut_osc_create(&ud.lfo);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_panst_init(ut, ud.panst);
    ud.panst->type = 0;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ut_osc_init(ut, ud.lfo, ud.ft, 0);
    ud.lfo->amp = 1;
    ud.lfo->freq = 0.5;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_panst_destroy(&ud.panst);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_osc_destroy(&ud.lfo);

    ut_destroy(&ut);
    return 0;
}
