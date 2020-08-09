#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_wavin *wavin;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT wavin = 0;
    ut_wavin_compute(ut, ud->wavin, NULL, &wavin);
    ut->out[0] = wavin;
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 1234567);

    ut_wavin_create(&ud.wavin);

    ut_wavin_init(ut, ud.wavin, "oneart.wav");

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_wavin_destroy(&ud.wavin);

    ut_destroy(&ut);
    return 0;
}
