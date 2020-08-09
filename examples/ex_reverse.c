#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_osc *osc;
    ut_ftbl *ft;
    ut_tenv *tenv;
    ut_reverse *rv;
} UserData;

void write_osc(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT env = 0;
    UTFLOAT osc = 0;
    UTFLOAT rv = 0;
    UTFLOAT dry = 0;
    UTFLOAT trig;
    if(ut->pos == 0){
        trig = 1.0;
    }else{
        trig = 0.0;
    }
    ut_tenv_compute(ut, ud->tenv, &trig, &env);
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    dry = osc * env;
    ut_reverse_compute(ut, ud->rv, &dry, &rv);
    ut->out[0] = dry + rv;
}

int main() {
    srand(time(NULL));
    UserData ud;
    uint32_t bufsize;
    ut_data *ut;
    ut_create(&ut);

    ut_reverse_create(&ud.rv);
    ut_tenv_create(&ud.tenv);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_osc_create(&ud.osc);

    ut_reverse_init(ut, ud.rv, 1.0);
    ut_tenv_init(ut, ud.tenv);
    ud.tenv->atk = 0.03;
    ud.tenv->hold = 0.01;
    ud.tenv->rel =  0.3;

    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->freq = 1000;
    ud.osc->amp = 0.5;
    ut->len = 44100 * 5;
    ut_process(ut, &ud, write_osc);

    ut_reverse_destroy(&ud.rv);
    ut_tenv_destroy(&ud.tenv);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_destroy(&ut);
    return 0;
}
