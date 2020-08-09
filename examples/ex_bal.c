#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_osc *osc[3];
    ut_ftbl *ft;
    ut_moogladder *filt;
    ut_bal *bal;
    ut_tenv *env;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    int i;
    UTFLOAT out = 0, osc = 0, filt = 0, bal = 0, env = 0, tick;
    for(i = 0; i < 3; i++) {
       ut_osc_compute(ut, ud->osc[i], NULL, &osc);
       out += osc * 0.5;
    }
    tick = (ut->pos == 0) ? 1.0 : 0.0;
    ut_tenv_compute(ut, ud->env, &tick, &env);
    ud->filt->freq = 300 + 3000 * env;
    ut_moogladder_compute(ut, ud->filt, &out, &filt);
    ut_bal_compute(ut, ud->bal, &filt, &osc, &bal);
    ut->out[0] = bal * env;
}

int main() {
    srand(time(NULL));
    int i;
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_ftbl_create(ut, &ud.ft, 4096);
    for(i = 0; i < 3; i++) {
        ut_osc_create(&ud.osc[i]);
        ud.osc[i]->amp = 0.5;
    }
    ut_bal_create(&ud.bal);
    ut_moogladder_create(&ud.filt);
    ud.filt->res = 0.8;
    ut_tenv_create(&ud.env);

    ut_gen_line(ut, ud.ft, "0 1 4096 -1");
    ut_osc_init(ut, ud.osc[0], ud.ft, 0);
    ud.osc[0]->freq = ut_midi2cps(41 - 0.05);
    ut_osc_init(ut, ud.osc[1], ud.ft, 0);
    ud.osc[1]->freq = ut_midi2cps(41 - 12);
    ut_osc_init(ut, ud.osc[2], ud.ft, 0);
    ud.osc[2]->freq = ut_midi2cps(41 + 0.05);
    ut->len = 44100 * 5;
    ut_bal_init(ut, ud.bal);
    ut_moogladder_init(ut, ud.filt);
    ut_tenv_init(ut, ud.env);
    ud.env->atk = 2.25;
    ud.env->hold = 0.5;
    ud.env->rel =  2.25;


    ut_process(ut, &ud, process);

    ut_ftbl_destroy(&ud.ft);
    for(i = 0; i < 3; i++) ut_osc_destroy(&ud.osc[i]);
    ut_bal_destroy(&ud.bal);
    ut_moogladder_destroy(&ud.filt);
    ut_tenv_destroy(&ud.env);
    ut_destroy(&ut);
    return 0;
}
