#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_prop *prop;
    ut_osc *osc;
    ut_ftbl *ft;
    ut_tenv *tenv;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, prop = 0, tenv = 0;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut_prop_compute(ut, ud->prop, NULL, &prop);
    ut_tenv_compute(ut, ud->tenv, &prop, &tenv);
    ut->out[0] = osc * tenv;
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 123345);

    ut_prop_create(&ud.prop);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_tenv_create(&ud.tenv);

    ut_prop_init(ut, ud.prop, "2(+{3(+++)|+}){4(+?+?)|+|-}");
    ud.prop->bpm = 80;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ut_tenv_init(ut, ud.tenv);
    ud.tenv->atk = 0.003;
    ud.tenv->hold = 0.001;
    ud.tenv->rel =  0.2;

    ud.osc->freq = 500;

    ut->len = 44100 * 20;
    ut_process(ut, &ud, process);

    ut_prop_destroy(&ud.prop);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_tenv_destroy(&ud.tenv);

    ut_destroy(&ut);
    return 0;
}
