#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_tabread *tr;
    ut_ftbl *ft;
    ut_phasor *phasor;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT tab = 0.0, phasor = 0.0;
    ut_phasor_compute(ut, ud->phasor, NULL, &phasor);
    ud->tr->index = phasor;
    ut_tabread_compute(ut, ud->tr, NULL, &tab);
    ut->out[0] = tab;
}

int main() {
    srand(time(NULL));
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_tabread_create(&ud.tr);

    ut_phasor_create(&ud.phasor);

    ut_ftbl_create(ut, &ud.ft, 395393);
    ut_gen_file(ut, ud.ft, "oneart.wav");

    ut_tabread_init(ut, ud.tr, ud.ft, 1);

    /* since mode = 1, offset 5% into file */
    ud.tr->offset = 0.05;
    /* no wraparound */
    ud.tr->wrap = 0;

    ut_phasor_init(ut, ud.phasor, 0);
    /* set playback rate to half speed, or 1/(t * 2) */
    ud.phasor->freq = 1 / (8.97 * 2);
    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_phasor_destroy(&ud.phasor);
    ut_tabread_destroy(&ud.tr);
    ut_ftbl_destroy(&ud.ft);
    ut_destroy(&ut);
    return 0;
}
