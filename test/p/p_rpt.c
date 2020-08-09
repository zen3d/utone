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
    UTFLOAT in = 0, out = 0, trig = 0;

    ut_rpt *unit[NUM];

    for(u = 0; u < NUM; u++) { 
        ut_rpt_create(&unit[u]);
        ut_rpt_init(ut, unit[u], 2.0);
    }

    for(t = 0; t < ut->len; t++) {
        for(u = 0; u < NUM; u++) ut_rpt_compute(ut, unit[u], &trig, &in, &out);
    }

    for(u = 0; u < NUM; u++) ut_rpt_destroy(&unit[u]);

    ut_destroy(&ut);
    return 0;
}

