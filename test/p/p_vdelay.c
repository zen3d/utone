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

    ut_vdelay *unit[NUM];

    for(u = 0; u < NUM; u++) { 
        ut_vdelay_create(&unit[u]);
        ut_vdelay_init(ut, unit[u], 1.0);
    }

    for(t = 0; t < ut->len; t++) {
        for(u = 0; u < NUM; u++) ut_vdelay_compute(ut, unit[u], &in, &out);
    }

    for(u = 0; u < NUM; u++) ut_vdelay_destroy(&unit[u]);

    ut_destroy(&ut);
    return 0;
}

