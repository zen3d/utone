#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_osc *osc;
    ut_ftbl *ft; 
    ut_tevent *te;
    int counter;
    UTFLOAT freq;
} UserData;

void write_osc(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT trig = 0;
    if(ud->counter == 0){
        trig = 1.0;
    }
    ut_tevent_compute(ut, ud->te, &trig, &ud->osc->freq);
    ut_osc_compute(ut, ud->osc, NULL, &ut->out[0]);
    ud->counter = (ud->counter + 1) % 4410;
}

void freq_reinit(void *ud){
    UTFLOAT *freq = ud;
    *freq = 500 + rand() % 2000;
}

void freq_compute(void *ud, UTFLOAT *out){
    UTFLOAT *freq = ud;
    *out = *freq;
}

int main() {
    srand(time(NULL));
    UserData ud;
    UTFLOAT *freqp = &ud.freq;
    ud.counter = 0;
    ud.freq = 400;
    ut_data *ut;
    ut_create(&ut);
    ut_tevent_create(&ud.te);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_osc_create(&ud.osc);

    ut_tevent_init(ut, ud.te, freq_reinit, freq_compute, freqp);
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->freq = *freqp;
    ut->len = 44100 * 5;
    ut_process(ut, &ud, write_osc);

    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_tevent_destroy(&ud.te);
    ut_destroy(&ut);
    return 0;
}
