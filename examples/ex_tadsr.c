#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_tadsr *tadsr;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, tadsr = 0, trig = 0;
    if(ut->pos == 0 || ut->pos == ut->sr * 2) trig = 1;
    ut_tadsr_compute(ut, ud->tadsr, &trig, &tadsr);
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut->out[0] = osc * tadsr;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_tadsr_create(&ud.tadsr);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_tadsr_init(ut, ud.tadsr);
    ud.tadsr->atk = 0.1;
    ud.tadsr->dec = 0.2;
    ud.tadsr->sus = 0.3;
    ud.tadsr->rel = 0.1;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_tadsr_destroy(&ud.tadsr);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    ut_destroy(&ut);
    return 0;
}
