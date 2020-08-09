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

    ut_pan2 *unit[NUM];

    for(u = 0; u < NUM; u++) { 
        ut_pan2_create(&unit[u]);
        ut_pan2_init(ut, unit[u]);
        unit[u]->type  = 1;
    }

    for(t = 0; t < ut->len; t++) {
        for(u = 0; u < NUM; u++) ut_pan2_compute(ut, unit[u], &in, 
                &out1, &out2);
    }

    for(u = 0; u < NUM; u++) ut_pan2_destroy(&unit[u]);

    ut_destroy(&ut);
    return 0;
}

