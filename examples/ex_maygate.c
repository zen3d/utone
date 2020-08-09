#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_osc *osc;
    ut_ftbl *ft;
    ut_tevent *te;
    ut_metro *met;
    ut_tenv *tenv;
    ut_maygate *mg;
    UTFLOAT freq;
} UserData;

void write_osc(ut_data *data, void *ud) {
    UserData *udp = ud;
    UTFLOAT trig = 0;
    UTFLOAT env = 0;
    UTFLOAT osc = 0;
    UTFLOAT mgate = 0;
    ut_metro_compute(data, udp->met, NULL, &trig);
    ut_maygate_compute(data, udp->mg, &trig, &mgate);
    ut_tevent_compute(data, udp->te, &trig, &udp->osc->freq);
    ut_tenv_compute(data, udp->tenv, &trig, &env);
    ut_osc_compute(data, udp->osc, NULL, &osc);
    data->out[0] = osc * env * mgate;
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
    ud.freq = 400;
    ut_data *ut;
    ut_create(&ut);

    ut_maygate_create(&ud.mg);
    ut_tenv_create(&ud.tenv);
    ut_metro_create(&ud.met);
    ut_tevent_create(&ud.te);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_osc_create(&ud.osc);

    ut_maygate_init(ut, ud.mg);
    ud.mg->prob = 0.2;
    ut_tenv_init(ut, ud.tenv);
    ud.tenv->atk = 0.01;
    ud.tenv->hold = 0.01;
    ud.tenv->rel =  0.2;

    ut_metro_init(ut, ud.met);
    ud.met->freq = 12;
    ut_tevent_init(ut, ud.te, freq_reinit, freq_compute, freqp);
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->freq = *freqp;
    ut->len = 44100 * 5;

    ut_process(ut, &ud, write_osc);

    ut_maygate_destroy(&ud.mg);
    ut_tenv_destroy(&ud.tenv);
    ut_metro_destroy(&ud.met);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_tevent_destroy(&ud.te);
    ut_destroy(&ut);
    return 0;
}
