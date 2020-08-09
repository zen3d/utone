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
    ut_metro *met;
    ut_incr *incr;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

void process(ut_data *ut, void *udata) 
{
    UserData *ud = udata;
    UTFLOAT osc = 0, incr = 0, met = 0;
    ut_metro_compute(ut, ud->met, NULL, &met);
    ut_incr_compute(ut, ud->incr, &met, &incr);
    ud->osc->freq = incr;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut->out[0] = osc;
}

int main() 
{
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 1234567);

    ut_metro_create(&ud.met);
    ut_incr_create(&ud.incr);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_metro_init(ut, ud.met);
    ud.met->freq = 3;
    ut_incr_init(ut, ud.incr, 300);
    ud.incr->min = 300;
    ud.incr->max = 900;
    ud.incr->step = 30;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->amp = 0.5;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_incr_destroy(&ud.incr);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_metro_destroy(&ud.met);

    ut_destroy(&ut);
    return 0;
}
