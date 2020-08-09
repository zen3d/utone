#include "utone.h"

typedef struct{
    ut_osc *osc;
    ut_ftbl *ft;
    ut_metro *mt;
    ut_tenv *te;
    ut_rpt *rpt;
    ut_maygate *mg;
} UserData;

void compute(ut_data *ut, void *udata){
    UserData *ud = udata;
    UTFLOAT met, osc, env, rpt, maygate, trig, dry;
    ut_metro_compute(ut, ud->mt, NULL, &met);
    ut_tenv_compute(ut, ud->te, &met, &env);
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    dry = osc * env;
    ut_maygate_compute(ut, ud->mg, &met, &maygate);
    trig = met * maygate;
    ut_rpt_compute(ut, ud->rpt, &trig, &dry, &rpt);
    ut->out[0] = rpt;
}

int main(){
    ut_data *ut;
    UserData ud;
    ut_create(&ut);
    int tempo = 120;
    ut_rpt_create(&ud.rpt);
    ut_maygate_create(&ud.mg);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 4096);
    ut_metro_create(&ud.mt);
    ut_tenv_create(&ud.te);


    ut_maygate_init(ut, ud.mg);
    ud.mg->prob = 0.5;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ut_metro_init(ut, ud.mt);
    ud.mt->freq = tempo / 60.0;
    ut_rpt_init(ut, ud.rpt, 1.0);
    ud.rpt->bpm = tempo;
    ud.rpt->div = 8;
    ud.rpt->rep = 4;
    ut_tenv_init(ut, ud.te);
    ud.te->atk = 0.001;
    ud.te->hold = 0.1;
    ud.te->rel =  0.1;

    ut_process(ut, &ud, compute);

    ut_tenv_destroy(&ud.te);
    ut_metro_destroy(&ud.mt);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_rpt_destroy(&ud.rpt);

    ut_destroy(&ut);
    return 0;
}
