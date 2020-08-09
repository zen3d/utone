#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_pitchamdf *pitchamdf;
    ut_osc *osc;
    ut_ftbl *ft;
    ut_blsaw *blsaw;
    ut_randh *randh;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT freq = 0, amp = 0, blsaw = 0, randh = 0, osc = 0;
    ut_randh_compute(ut, ud->randh, NULL, &randh);
    *ud->blsaw->freq = randh;
    ut_blsaw_compute(ut, ud->blsaw, NULL, &blsaw);
    ut_pitchamdf_compute(ut, ud->pitchamdf, &blsaw, &freq, &amp);
    ud->osc->freq = freq;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut->out[0] = osc;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_pitchamdf_create(&ud.pitchamdf);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_blsaw_create(&ud.blsaw);
    ut_randh_create(&ud.randh);

    ut_pitchamdf_init(ut, ud.pitchamdf, 200, 500);
    ut_randh_init(ut, ud.randh);
    ud.randh->max = 500;
    ud.randh->min = 200;
    ud.randh->freq = 6;

    ut_blsaw_init(ut, ud.blsaw);

    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_blsaw_destroy(&ud.blsaw);
    ut_randh_destroy(&ud.randh);
    ut_pitchamdf_destroy(&ud.pitchamdf);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    ut_destroy(&ut);
    return 0;
}
