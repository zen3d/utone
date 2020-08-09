#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_diskin *diskin;
    ut_conv *conv;
    ut_ftbl *ft; 
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT conv = 0, diskin = 0, bal = 0;
    ut_diskin_compute(ut, ud->diskin, NULL, &diskin);
    ut_conv_compute(ut, ud->conv, &diskin, &conv);
    ut->out[0] = conv * 0.05;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_diskin_create(&ud.diskin);
    ut_conv_create(&ud.conv);
    ut_ftbl_loadfile(ut, &ud.ft, "imp.wav");

    ut_diskin_init(ut, ud.diskin, "oneart.wav");
    ut_conv_init(ut, ud.conv, ud.ft, 8192);

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_conv_destroy(&ud.conv);
    ut_ftbl_destroy(&ud.ft);
    ut_diskin_destroy(&ud.diskin);

    ut_destroy(&ut);
    return 0;
}
