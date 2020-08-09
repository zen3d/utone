/*
 * This is a dummy example.
 * Please implement a small and simple working example of your module, and then
 * remove this header.
 * Don't be clever.
 * Bonus points for musicality. 
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_peaklim *peaklim;
    ut_diskin *diskin;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT diskin = 0, peaklim = 0;
    ut_diskin_compute(ut, ud->diskin, NULL, &diskin);
    ut_peaklim_compute(ut, ud->peaklim, &diskin, &peaklim);
    ut->out[0] = peaklim;
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 1234567);

    ut_peaklim_create(&ud.peaklim);
    ut_diskin_create(&ud.diskin);

    ut_peaklim_init(ut, ud.peaklim);
    ud.peaklim->atk = 0.1;
    ud.peaklim->rel = 0.1;
    ud.peaklim->thresh = -30;
    ut_diskin_init(ut, ud.diskin, "oneart.wav");


    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_peaklim_destroy(&ud.peaklim);
    ut_diskin_destroy(&ud.diskin);

    ut_destroy(&ut);
    return 0;
}
