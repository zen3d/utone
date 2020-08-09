#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_tgate *tgate;
    ut_osc *osc;
    ut_ftbl *ft; 
    ut_dmetro *dm;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, tgate = 0;
    UTFLOAT dm = 0;
    ut_dmetro_compute(ut, ud->dm, NULL, &dm);
    ut_tgate_compute(ut, ud->tgate, &dm, &tgate);
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut->out[0] = osc * tgate;
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 1234567);

    ut_tgate_create(&ud.tgate);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_dmetro_create(&ud.dm);

    ut_tgate_init(ut, ud.tgate);
    ud.tgate->time = 0.2;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->freq = 1000;
    ut_dmetro_init(ut, ud.dm);
    ud.dm->time = 0.5;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_tgate_destroy(&ud.tgate);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_dmetro_destroy(&ud.dm);

    ut_destroy(&ut);
    return 0;
}
