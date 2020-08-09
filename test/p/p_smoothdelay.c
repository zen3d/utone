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

    ut_smoothdelay *unit[NUM];

    for(u = 0; u < NUM; u++) { 
        ut_smoothdelay_create(&unit[u]);
        ut_smoothdelay_init(ut, unit[u], 1.0, 1024);
    }

    for(t = 0; t < ut->len; t++) {
        for(u = 0; u < NUM; u++) ut_smoothdelay_compute(ut, unit[u], &in, &out);
    }

    for(u = 0; u < NUM; u++) ut_smoothdelay_destroy(&unit[u]);

    ut_destroy(&ut);
    return 0;
}

