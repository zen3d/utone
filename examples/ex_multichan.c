#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_osc *osc1, *osc2;
    ut_ftbl *ft;
    int counter1, counter2;
} UserData;

void write_osc(ut_data *ut, void *udata) {
    UserData *ud = udata;
    if(ud->counter1 == 0){
        ud->osc1->freq = 500 + rand() % 2000;
    }
    if(ud->counter2 == 0){
        ud->osc2->freq = 500 + rand() % 2000;
    }
    ut_osc_compute(ut, ud->osc1, NULL, &ut->out[0]);
    ut_osc_compute(ut, ud->osc2, NULL, &ut->out[1]);
    ud->counter1 = (ud->counter1 + 1) % 4410;
    ud->counter2 = (ud->counter2 + 1) % 8000;
}

int main() {
    srand(time(NULL));
    UserData ud;
    ud.counter1 = 0;
    ud.counter2 = 0;
    ut_data *ut;
    /* two channels will write 0_test.wav and 1_test.wav */
    ut_createn(&ut, 2);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_osc_create(&ud.osc1);
    ut_osc_create(&ud.osc2);

    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc1, ud.ft, 0);
    ud.osc1->freq = 500;
    ut_osc_init(ut, ud.osc2, ud.ft, 0);
    ud.osc2->freq = 500;
    ut->len = 44100 * 5;
    ut_process(ut, &ud, write_osc);

    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc1);
    ut_osc_destroy(&ud.osc2);
    ut_destroy(&ut);
    return 0;
}
