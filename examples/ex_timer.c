#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_timer *timer;
    ut_osc *osc;
    ut_ftbl *ft; 
    ut_tenv *tenv;
    ut_dmetro *dmetro;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, timer = 0, clock = 0, tenv = 0;

    if(ut->pos % 20000 == 0) {
        clock = 1;
    }
    ut_timer_compute(ut, ud->timer, &clock, &timer);
    ud->dmetro->time = timer;
    ut_dmetro_compute(ut, ud->dmetro, NULL, &timer);
    ut_tenv_compute(ut, ud->tenv, &timer, &tenv);
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut->out[0] = osc * tenv;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_timer_create(&ud.timer);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_tenv_create(&ud.tenv);
    ut_dmetro_create(&ud.dmetro);

    ut_timer_init(ut, ud.timer);
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ut_tenv_init(ut, ud.tenv);
    ud.tenv->atk = 0.1;
    ud.tenv->hold= 0.1;
    ud.tenv->rel = 0.1;
    ut_dmetro_init(ut, ud.dmetro);

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_timer_destroy(&ud.timer);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_tenv_destroy(&ud.tenv);
    ut_dmetro_destroy(&ud.dmetro);

    ut_destroy(&ut);
    return 0;
}
