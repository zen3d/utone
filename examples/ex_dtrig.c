#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_osc *osc;
    ut_ftbl *ft, *delta;
    ut_tenv *tenv;
    ut_dtrig *dt;
} UserData;

void write_osc(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT env = 0;
    UTFLOAT osc = 0;
    UTFLOAT dry = 0;
    UTFLOAT trig;
    UTFLOAT dtrig = 0;
    if(ut->pos == 0){
        trig = 1.0;
    }else{
        trig = 0.0;
    }
    ut_dtrig_compute(ut, ud->dt, &trig, &dtrig);
    ut_tenv_compute(ut, ud->tenv, &dtrig, &env);
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut->out[0] = osc * env;
}

int main() {
    srand(time(NULL));
    UserData ud;
    uint32_t bufsize;
    ut_data *ut;
    ut_create(&ut);
    ut_auxdata rvaux;

    ut_dtrig_create(&ud.dt);
    ut_tenv_create(&ud.tenv);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_ftbl_create(ut, &ud.delta, 4);
    ut_osc_create(&ud.osc);

    ud.delta->tbl[0] = 1.0;
    ud.delta->tbl[1] = 1.0;
    ud.delta->tbl[2] = 0.5;
    ud.delta->tbl[3] = 0.5;
    ut_dtrig_init(ut, ud.dt, ud.delta);
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

    ut_dtrig_destroy(&ud.dt);
    ut_tenv_destroy(&ud.tenv);
    ut_ftbl_destroy(&ud.ft);
    ut_ftbl_destroy(&ud.delta);
    ut_osc_destroy(&ud.osc);
    ut_destroy(&ut);
    return 0;
}
