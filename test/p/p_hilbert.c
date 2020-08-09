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
    UTFLOAT in = 0, out1 = 0, out2 = 0;

    ut_hilbert *unit[NUM];

    for(u = 0; u < NUM; u++) { 
        ut_hilbert_create(&unit[u]);
        ut_hilbert_init(ut, unit[u]);
    }

    for(t = 0; t < ut->len; t++) {
        for(u = 0; u < NUM; u++) ut_hilbert_compute(ut, unit[u], &in, 
                &out1, &out2);
    }

    for(u = 0; u < NUM; u++) ut_hilbert_destroy(&unit[u]);

    ut_destroy(&ut);
    return 0;
}

