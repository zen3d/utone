#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_fold *fold;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, fold = 0;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut_fold_compute(ut, ud->fold, &osc, &fold);
    ut->out[0] = fold;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_fold_create(&ud.fold);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_fold_init(ut, ud.fold);
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_fold_destroy(&ud.fold);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    ut_destroy(&ut);
    return 0;
}
