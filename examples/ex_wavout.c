#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_wavout *wavout;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, wavout = 0;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut_wavout_compute(ut, ud->wavout, &osc, &wavout);
    ut->out[0] = wavout;
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 1234567);

    ut_wavout_create(&ud.wavout);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_wavout_init(ut, ud.wavout, "wavout.wav");
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    printf("file wavout.wav written to disk.\n");
    ut_wavout_destroy(&ud.wavout);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    ut_destroy(&ut);
    return 0;
}
