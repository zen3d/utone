#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_scale *scale;
    ut_osc *osc;
    ut_ftbl *ft;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, scale = 0;
    /* constant set to 1, when scaled, it becomes 440 */
    UTFLOAT val = 1;
    ut_scale_compute(ut, ud->scale, &val, &scale);
    ud->osc->freq = scale;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut->out[0] = osc;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_scale_create(&ud.scale);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_scale_init(ut, ud.scale);
    ud.scale->min = 0;
    ud.scale->max = 880;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->amp = 0.1;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_scale_destroy(&ud.scale);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    ut_destroy(&ut);
    return 0;
}
