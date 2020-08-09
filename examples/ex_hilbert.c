#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_hilbert *hilbert;
    ut_osc *cos, *sin;
    ut_ftbl *ft; 
    ut_diskin *diskin;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT disk= 0;
    UTFLOAT real = 0, imag = 0;
    UTFLOAT diskin = 0;
    UTFLOAT sin = 0, cos = 0;

    ut_diskin_compute(ut, ud->diskin, NULL, &diskin);
    ut_osc_compute(ut, ud->sin, NULL, &sin);
    ut_osc_compute(ut, ud->cos, NULL, &cos);
    ut_hilbert_compute(ut, ud->hilbert, &diskin, &real, &imag);
    ut->out[0] = ((cos * real) + (sin * real)) * 0.7;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_hilbert_create(&ud.hilbert);
    ut_osc_create(&ud.sin);
    ut_osc_create(&ud.cos);
    ut_diskin_create(&ud.diskin);
    ut_ftbl_create(ut, &ud.ft, 8192);

    ut_hilbert_init(ut, ud.hilbert);
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.sin, ud.ft, 0);
    ut_osc_init(ut, ud.cos, ud.ft, 0.25);
    ud.sin->freq = 1000;
    ud.cos->freq = 1000;
    ut_diskin_init(ut, ud.diskin, "oneart.wav");

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_hilbert_destroy(&ud.hilbert);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.sin);
    ut_osc_destroy(&ud.cos);
    ut_diskin_destroy(&ud.diskin);

    ut_destroy(&ut);
    return 0;
}
