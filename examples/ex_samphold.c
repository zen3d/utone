#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_samphold *samphold;
    ut_osc *osc;
    ut_ftbl *ft;
    ut_metro *met;
    ut_noise *noise;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, samphold = 0, met = 0, noise = 0;
    ut_metro_compute(ut, ud->met, NULL, &met);
    ut_noise_compute(ut, ud->noise, NULL, &noise);
    ut_samphold_compute(ut, ud->samphold, &met, &noise, &samphold);
    ud->osc->freq = 200 + (samphold + 1) * 300;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut->out[0] = osc;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_samphold_create(&ud.samphold);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_metro_create(&ud.met);
    ut_noise_create(&ud.noise);

    ut_samphold_init(ut, ud.samphold);
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ut_metro_init(ut, ud.met);
    ud.met->freq = 5;
    ut_noise_init(ut, ud.noise);
    ud.noise->amp = 1;
    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_samphold_destroy(&ud.samphold);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_metro_destroy(&ud.met);
    ut_noise_destroy(&ud.noise);

    ut_destroy(&ut);
    return 0;
}
