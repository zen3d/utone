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
    UTFLOAT in = 0, rms = 0, cps = 0;

    ut_pitchamdf *unit[NUM];

    for(u = 0; u < NUM; u++) { 
        ut_pitchamdf_create(&unit[u]);
        ut_pitchamdf_init(ut, unit[u], 100, 400);
    }

    for(t = 0; t < ut->len; t++) {
        for(u = 0; u < NUM; u++) ut_pitchamdf_compute(ut, unit[u], &in, &cps, &rms);
    }

    for(u = 0; u < NUM; u++) ut_pitchamdf_destroy(&unit[u]);

    ut_destroy(&ut);
    return 0;
}

