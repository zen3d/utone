#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_fosc *osc;
    ut_ftbl *ft; 
    ut_jitter *jit;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT jit = 0;
    ut_jitter_compute(ut, ud->jit, NULL, &jit);
    ud->osc->freq = ut_midi2cps(60 + jit);
    ut_fosc_compute(ut, ud->osc, NULL, &ut->out[0]);
}

int main() {
    srand(time(NULL));
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_fosc_create(&ud.osc);
    ut_jitter_create(&ud.jit);   

    ut_gen_sine(ut, ud.ft);
    ut_fosc_init(ut, ud.osc, ud.ft);
    ut_jitter_init(ut, ud.jit);
    ud.jit->cpsMin = 0.5;
    ud.jit->cpsMax = 4;
    ud.jit->amp = 3;  
    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_ftbl_destroy(&ud.ft);
    ut_fosc_destroy(&ud.osc);
    ut_jitter_destroy(&ud.jit);

    ut_destroy(&ut);
    return 0;
}
