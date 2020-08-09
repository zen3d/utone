#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_diskin *diskin;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT diskin = 0;
    ut_diskin_compute(ut, ud->diskin, NULL, &diskin);
    ut->out[0] = diskin;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_diskin_create(&ud.diskin);

    ut_diskin_init(ut, ud.diskin, "oneart.wav");

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_diskin_destroy(&ud.diskin);

    ut_destroy(&ut);
    return 0;
}
