#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_pareq *pareq;
    ut_noise *noise;
    ut_ftbl *ft; 
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT noise = 0, pareq = 0;
    ut_noise_compute(ut, ud->noise, NULL, &noise);
    ut_pareq_compute(ut, ud->pareq, &noise, &pareq);
    ut->out[0] = pareq;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_pareq_create(&ud.pareq);
    ut_noise_create(&ud.noise);

    ut_pareq_init(ut, ud.pareq);
    ud.pareq->fc = 500;
    ut_noise_init(ut, ud.noise);
    ud.noise->amp = 0.4;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_pareq_destroy(&ud.pareq);
    ut_noise_destroy(&ud.noise);

    ut_destroy(&ut);
    return 0;
}
