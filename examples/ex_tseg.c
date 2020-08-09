#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_tseg *tseg;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, tseg = 0;
    UTFLOAT trig = (ut->pos == 0);
    ut_tseg_compute(ut, ud->tseg, &trig, &tseg);
    ud->osc->freq = 100 + (tseg * 1000);
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut->out[0] = osc;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_tseg_create(&ud.tseg);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_tseg_init(ut, ud.tseg, 0.0001);
    ud.tseg->end = 1.0;
    ud.tseg->type = 3.0;
    ud.tseg->dur = 4.0;

    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_tseg_destroy(&ud.tseg);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    ut_destroy(&ut);
    return 0;
}
