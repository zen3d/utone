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

    ut_fof *unit[NUM];

    ut_ftbl *sine;
    ut_ftbl *win;

    ut_ftbl_create(ut, &sine, 2048);
    ut_ftbl_create(ut, &win, 1024);

    for(u = 0; u < NUM; u++) { 
        ut_fof_create(&unit[u]);
        ut_fof_init(ut, unit[u], sine, win, 100, 0);
    }
    

    for(t = 0; t < ut->len; t++) {
        for(u = 0; u < NUM; u++) ut_fof_compute(ut, unit[u], &in, &out);
    }

    for(u = 0; u < NUM; u++) ut_fof_destroy(&unit[u]);
    ut_ftbl_destroy(&sine);
    ut_ftbl_destroy(&win);

    ut_destroy(&ut);
    return 0;
}

