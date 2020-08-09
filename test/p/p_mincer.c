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

    ut_mincer *unit[NUM];
    ut_ftbl *wav;

    ut_ftbl_loadfile(ut, &wav, SAMPDIR "oneart.wav");

    for(u = 0; u < NUM; u++) { 
        ut_mincer_create(&unit[u]);
        ut_mincer_init(ut, unit[u], wav, 2048);
    }

    for(t = 0; t < ut->len; t++) {
        for(u = 0; u < NUM; u++) ut_mincer_compute(ut, unit[u], &in, &out);
    }

    for(u = 0; u < NUM; u++) ut_mincer_destroy(&unit[u]);

    ut_destroy(&ut);
    ut_ftbl_destroy(&wav);
    return 0;
}

