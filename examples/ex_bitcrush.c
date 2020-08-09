#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_bitcrush *bitcrush;
    ut_diskin *file;
    ut_ftbl *ft;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT disk = 0, bitcrush = 0;
    ut_diskin_compute(ut, ud->file, NULL, &disk);
    ut_bitcrush_compute(ut, ud->bitcrush, &disk, &bitcrush);
    ut->out[0] = bitcrush;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_bitcrush_create(&ud.bitcrush);
    ut_diskin_create(&ud.file);

    ut_diskin_init(ut, ud.file, "oneart.wav");
    ut_bitcrush_init(ut, ud.bitcrush);
    ud.bitcrush->bitdepth = 8;
    ud.bitcrush->srate = 10000;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_bitcrush_destroy(&ud.bitcrush);
    ut_diskin_destroy(&ud.file);

    ut_destroy(&ut);
    return 0;
}
