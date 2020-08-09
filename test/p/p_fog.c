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
    ut_ftbl *wav;
    ut_ftbl *win;

    ut_fog *unit[NUM];
    
    ut_ftbl_loadfile(ut, &wav, SAMPDIR "oneart.wav");
    ut_ftbl_create(ut, &win, 1024);
    ut_gen_composite(ut, win, "0.5 0.5 270 0.5");

    for(u = 0; u < NUM; u++) { 
        ut_fog_create(&unit[u]);
        ut_fog_init(ut, unit[u], win, wav, 100, 0);
    }

    for(t = 0; t < ut->len; t++) {
        for(u = 0; u < NUM; u++) ut_fog_compute(ut, unit[u], &in, &out);
    }

    for(u = 0; u < NUM; u++) ut_fog_destroy(&unit[u]);

    ut_destroy(&ut);
    ut_ftbl_destroy(&wav);
    ut_ftbl_destroy(&win);
    return 0;
}

