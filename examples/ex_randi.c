#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_osc *osc;
    ut_ftbl *ft; 
    ut_randi *rnd;
} UserData;

void write_osc(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT freq;
    ut_randi_compute(ut, ud->rnd, NULL, &freq);
    ud->osc->freq = freq;
    ut_osc_compute(ut, ud->osc, NULL, &ut->out[0]);
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 12345);
    ut_ftbl_create(ut, &ud.ft, 1024);
    ut_osc_create(&ud.osc);
    ut_randi_create(&ud.rnd);

    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ut_randi_init(ut, ud.rnd);
    
    ud.rnd->min = 300;  
    ud.rnd->max = 3000;  

    ut->len = 44100 * 5;

    ut_process(ut, &ud, write_osc);

    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_randi_destroy(&ud.rnd);
    ut_destroy(&ut);
    return 0;
}
