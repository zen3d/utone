#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_atone *atone;
    ut_noise *noise;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT noise = 0, atone = 0;
    ut_noise_compute(ut, ud->noise, NULL, &noise);
    ut_atone_compute(ut, ud->atone, &noise, &atone);
    ut->out[0] = atone;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_atone_create(&ud.atone);
    ut_noise_create(&ud.noise);

    ut_atone_init(ut, ud.atone);
    ut_noise_init(ut, ud.noise);

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_atone_destroy(&ud.atone);
    ut_noise_destroy(&ud.noise);

    ut_destroy(&ut);
    return 0;
}
