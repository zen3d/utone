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
    ut_pshift *pshift;
    ut_diskin *diskin;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT diskin = 0, pshift = 0;
    ut_diskin_compute(ut, ud->diskin, NULL, &diskin);
    ut_pshift_compute(ut, ud->pshift, &diskin, &pshift);
    ut->out[0] = pshift;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_pshift_create(&ud.pshift);
    ut_diskin_create(&ud.diskin);    

    ut_pshift_init(ut, ud.pshift);
    *ud.pshift->shift = 7;
    *ud.pshift->window = 500;
    /* half window size is smoothest sounding */
    *ud.pshift->xfade = 250;
    ut_diskin_init(ut, ud.diskin, "oneart.wav");

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_pshift_destroy(&ud.pshift);
    ut_diskin_destroy(&ud.diskin);

    ut_destroy(&ut);
    return 0;
}
