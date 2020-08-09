#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_waveset *waveset;
    ut_diskin *diskin;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT wav = 0, waveset = 0;
    ut_diskin_compute(ut, ud->diskin, NULL, &wav);
    ut_waveset_compute(ut, ud->waveset, &wav, &waveset);
    ut_out(ut, 0, waveset);
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 1234567);

    ut_waveset_create(&ud.waveset);
    ut_diskin_create(&ud.diskin);

    ut_waveset_init(ut, ud.waveset, 1.0);
    ud.waveset->rep = 3.0;
    ut_diskin_init(ut, ud.diskin, "oneart.wav");

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_waveset_destroy(&ud.waveset);
    ut_diskin_destroy(&ud.diskin);

    ut_destroy(&ut);
    return 0;
}
