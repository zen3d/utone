
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
    UTFLOAT out = 0;

    ut_voc *unit[NUM];

    for(u = 0; u < NUM; u++) {
        ut_voc_create(&unit[u]);
        ut_voc_init(ut, unit[u]);
    }

    for(t = 0; t < ut->len; t++) {
        for(u = 0; u < NUM; u++) ut_voc_compute(ut, unit[u], &out);
    }

    for(u = 0; u < NUM; u++) ut_voc_destroy(&unit[u]);

    ut_destroy(&ut);
    return 0;
}

