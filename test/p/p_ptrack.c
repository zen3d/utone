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
    UTFLOAT in = 0, freq = 0, amp = 0;

    ut_ptrack *unit[NUM];

    for(u = 0; u < NUM; u++) { 
        ut_ptrack_create(&unit[u]);
        ut_ptrack_init(ut, unit[u], 512, 20);
    }

    for(t = 0; t < ut->len; t++) {
        for(u = 0; u < NUM; u++) ut_ptrack_compute(ut, unit[u], &in, 
                &freq, &amp);
    }

    for(u = 0; u < NUM; u++) ut_ptrack_destroy(&unit[u]);

    ut_destroy(&ut);
    return 0;
}

