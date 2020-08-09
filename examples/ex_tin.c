/*
 * This module is similar to "in", execpt that it will only read from STDIN
 * when triggered.
 *
 * This program expects to read UTFLOATs from STDIN, which control
 * the oscillator frequency in Hz. Here is one usage case, using Sporth
 * (paulbatchelor.github.io/proj/sporth):
 *
 * echo "0.5 noise 0.5 + 100 * 1000 +" | sporth -o raw -d 10 | ./ex_tin.bin
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_tin *in;
    ut_osc *osc;
    ut_ftbl *ft;
    ut_metro *met;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT in = 0, met = 0, osc = 0;
    ut_metro_compute(ut, ud->met, NULL, &met);
    ut_tin_compute(ut, ud->in, &met, &in);
    ud->osc->freq = in;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut->out[0] = osc;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_tin_create(&ud.in);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 4096);
    ut_metro_create(&ud.met);

    ut_tin_init(ut, ud.in);
    ut_metro_init(ut, ud.met);
    ud.met->freq = 2;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_tin_destroy(&ud.in);
    ut_metro_destroy(&ud.met);
    ut_osc_destroy(&ud.osc);
    ut_ftbl_destroy(&ud.ft);

    ut_destroy(&ut);
    return 0;
}
