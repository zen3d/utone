#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_rspline *rspline;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, rspline = 0;
    ut_rspline_compute(ut, ud->rspline, NULL, &rspline);
    ud->osc->freq = rspline;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut->out[0] = osc;
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 1234567);

    ut_rspline_create(&ud.rspline);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_rspline_init(ut, ud.rspline);
    ud.rspline->min = 300;
    ud.rspline->max = 900;
    ud.rspline->cps_min = 0.1;
    ud.rspline->cps_max = 3;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_rspline_destroy(&ud.rspline);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    ut_destroy(&ut);
    return 0;
}
