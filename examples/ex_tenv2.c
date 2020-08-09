#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_tenv2 *tenv2;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, tenv2 = 0, tick = 0;

    if(ut->pos == 0 || ut->pos == ut->sr * 1) tick = 1;

    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut_tenv2_compute(ut, ud->tenv2, &tick, &tenv2);
    ut->out[0] = osc * tenv2;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_tenv2_create(&ud.tenv2);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_tenv2_init(ut, ud.tenv2);
    ud.tenv2->atk = 3;
    ud.tenv2->rel = 1;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->amp = 0.6;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_tenv2_destroy(&ud.tenv2);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    ut_destroy(&ut);
    return 0;
}
