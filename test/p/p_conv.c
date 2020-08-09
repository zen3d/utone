#include <stdlib.h>
#include <stdio.h>
#include "utone.h"
#include "config.h"

int main() {
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 12345);
    ut->sr = SR;
    ut->len = ut->sr * LEN;
    uint32_t t, u;
    UTFLOAT in = 0, out = 0;
    ut_ftbl *ft;

    ut_conv *unit[NUM];

    ut_ftbl_loadfile(ut, &ft, SAMPDIR "oneart.wav");

    for(u = 0; u < NUM; u++) { 
        ut_conv_create(&unit[u]);
        ut_conv_init(ut, unit[u], ft, 2048);
    }

    for(t = 0; t < ut->len; t++) {
        for(u = 0; u < NUM; u++) ut_conv_compute(ut, unit[u], &in, &out);
    }

    for(u = 0; u < NUM; u++) ut_conv_destroy(&unit[u]);

    ut_ftbl_destroy(&ft);
    ut_destroy(&ut);
    return 0;
}

