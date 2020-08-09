#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_wpkorg35 *wpkorg35;
    ut_noise *noise;
    ut_randi *randi;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT noise = 0, wpkorg35 = 0, randi = 0;
    ut_randi_compute(ut, ud->randi, NULL, &randi);
    ut_noise_compute(ut, ud->noise, NULL, &noise);
    ud->wpkorg35->cutoff = randi;
    ut_wpkorg35_compute(ut, ud->wpkorg35, &noise, &wpkorg35);
    ut->out[0] = wpkorg35;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_wpkorg35_create(&ud.wpkorg35);
    ut_noise_create(&ud.noise);
    ut_randi_create(&ud.randi);

    ut_wpkorg35_init(ut, ud.wpkorg35);
    ud.wpkorg35->res = 1.99;
    ut_noise_init(ut, ud.noise);
    ud.noise->amp = 0.01;
    ut_randi_init(ut, ud.randi);
    ud.randi->min = 100;
    ud.randi->max = 3000;
    ud.randi->cps = 10;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_wpkorg35_destroy(&ud.wpkorg35);
    ut_noise_destroy(&ud.noise);
    ut_randi_destroy(&ud.randi);

    ut_destroy(&ut);
    return 0;
}
