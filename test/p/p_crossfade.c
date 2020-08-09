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
    UTFLOAT in1 = 0, out = 0, in2 = 0;

    ut_crossfade *unit[NUM];

    for(u = 0; u < NUM; u++) { 
        ut_crossfade_create(&unit[u]);
        ut_crossfade_init(ut, unit[u]);
    }

    for(t = 0; t < ut->len; t++) {
        for(u = 0; u < NUM; u++) ut_crossfade_compute(ut, unit[u], 
                &in1, &in2, &out);
    }

    for(u = 0; u < NUM; u++) ut_crossfade_destroy(&unit[u]);

    ut_destroy(&ut);
    return 0;
}

