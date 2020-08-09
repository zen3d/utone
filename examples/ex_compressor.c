#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_compressor *compressor;
    ut_diskin *diskin;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT diskin = 0, compressor = 0;
    ut_diskin_compute(ut, ud->diskin, NULL, &diskin);
    ut_compressor_compute(ut, ud->compressor, &diskin, &compressor);
    ut->out[0] = compressor;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_compressor_create(&ud.compressor);
    ut_diskin_create(&ud.diskin);

    ut_compressor_init(ut, ud.compressor);
    *ud.compressor->ratio = 4;
    *ud.compressor->thresh = -30;
    *ud.compressor->atk = 0.2;
    *ud.compressor->rel = 0.2;
    ut_diskin_init(ut, ud.diskin, "oneart.wav");

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_compressor_destroy(&ud.compressor);
    ut_diskin_destroy(&ud.diskin);

    ut_destroy(&ut);
    return 0;
}
