#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_biscale *biscale;
    ut_osc *osc;
    ut_ftbl *ft;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, biscale = 0;
    /* constant set to 1, when scaled, it becomes 440 */
    UTFLOAT val = 1;
    ut_biscale_compute(ut, ud->biscale, &val, &biscale);
    ud->osc->freq = biscale;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut->out[0] = osc;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_biscale_create(&ud.biscale);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_biscale_init(ut, ud.biscale);
    ud.biscale->min = 0;
    ud.biscale->max = 880;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->amp = 0.1;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_biscale_destroy(&ud.biscale);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    ut_destroy(&ut);
    return 0;
}
