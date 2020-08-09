
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_voc *voc;
    ut_osc *osc;
    ut_ftbl *ft;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, voc = 0;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    if(ut_voc_get_counter(ud->voc) == 0) {
        osc = 12 + 16 * (0.5 * (osc + 1));
        ut_voc_set_tongue_shape(ud->voc, osc, 2.9);
    }
    ut_voc_compute(ut, ud->voc, &voc);
    ut->out[0] = voc;
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 1234567);

    ut_voc_create(&ud.voc);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_voc_init(ut, ud.voc);
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->amp = 1;
    ud.osc->freq = 0.1;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_voc_destroy(&ud.voc);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    ut_destroy(&ut);
    return 0;
}

