#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_progress *progress;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, progress = 0;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut_progress_compute(ut, ud->progress, &osc, &progress);
    ut->out[0] = progress;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut->len = 44100 * 30;

    ut_progress_create(&ud.progress);
    ut_osc_create(&ud.osc);

    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_progress_init(ut, ud.progress);
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);

    ut_process(ut, &ud, process);

    ut_progress_destroy(&ud.progress);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    ut_destroy(&ut);
    return 0;
}
