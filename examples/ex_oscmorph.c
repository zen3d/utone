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
    ut_oscmorph *oscmorph;
    ut_ftbl *wt1;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, oscmorph = 0;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    osc = (1 + osc) * 0.5;
    ud->oscmorph->wtpos = osc;
    ut_oscmorph_compute(ut, ud->oscmorph, NULL, &oscmorph);
    ut->out[0] = oscmorph;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_oscmorph_create(&ud.oscmorph);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_ftbl_create(ut, &ud.wt1, 2048);

    ut_gen_line(ut, ud.wt1, "0 1 2048 -1");
    ut_gen_sine(ut, ud.ft);

    ut_ftbl *ft_array[] = {ud.wt1, ud.ft};
    ut_oscmorph_init(ut, ud.oscmorph, ft_array, 2, 0);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->freq = 1;
    ud.osc->amp = 1;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_oscmorph_destroy(&ud.oscmorph);
    ut_ftbl_destroy(&ud.ft);
    ut_ftbl_destroy(&ud.wt1);
    ut_osc_destroy(&ud.osc);
    
    ut_destroy(&ut);
    return 0;
}
