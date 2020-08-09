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

    ut_ftbl *ft[2];
    ut_ftbl *ft1;
    ut_ftbl *ft2;

    ut_oscmorph *unit[NUM];

    ut_ftbl_create(ut, &ft1, 4096);
    ut_gen_sine(ut, ft1);
    ut_ftbl_create(ut, &ft2, 4096);
    ut_gen_sinesum(ut, ft2, "1 1 1");

    ft[0] = ft1;
    ft[1] = ft2;

    for(u = 0; u < NUM; u++) { 
        ut_oscmorph_create(&unit[u]);
        ut_oscmorph_init(ut, unit[u], ft, 2, 0);
    }

    for(t = 0; t < ut->len; t++) {
        for(u = 0; u < NUM; u++) ut_oscmorph_compute(ut, unit[u], &in, &out);
    }

    for(u = 0; u < NUM; u++) ut_oscmorph_destroy(&unit[u]);

    ut_ftbl_destroy(&ft1);
    ut_ftbl_destroy(&ft2);
    ut_destroy(&ut);
    return 0;
}

