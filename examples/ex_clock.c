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
    ut_clock *clock;
    ut_osc *osc;
    ut_ftbl *ft; 
    ut_tenv *te;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, clock = 0, env = 0;
    UTFLOAT trig = 0;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut_clock_compute(ut, ud->clock, &trig, &clock);
    ut_tenv_compute(ut, ud->te, &clock, &env);
    ut_out(ut, 0, env * osc);
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 1234567);

    ut_clock_create(&ud.clock);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_tenv_create(&ud.te);

    ut_clock_init(ut, ud.clock);
    ud.clock->bpm = 130;
    ud.clock->subdiv = 4;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ut_tenv_init(ut, ud.te);
    ud.te->atk = 0.001;
    ud.te->hold = 0.001;
    ud.te->rel = 0.001;
    

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_clock_destroy(&ud.clock);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_tenv_destroy(&ud.te);

    ut_destroy(&ut);
    return 0;
}
