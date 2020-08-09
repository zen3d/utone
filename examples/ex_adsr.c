#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_adsr *adsr;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, adsr = 0, gate = 0;
    if(ut->pos < ut->sr * 3) {
        gate = 1;
    }
    ut_adsr_compute(ut, ud->adsr, &gate, &adsr);
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut->out[0] = adsr * osc;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_adsr_create(&ud.adsr);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_adsr_init(ut, ud.adsr);
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->amp = 0.5;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_adsr_destroy(&ud.adsr);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    ut_destroy(&ut);
    return 0;
}
