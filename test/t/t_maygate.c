#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_osc *osc;
    ut_ftbl *ft;
    ut_tevent *te;
    ut_metro *met;
    ut_tenv *tenv;
    ut_maygate *mg;
    UTFLOAT freq;
    ut_data *ut;
} UserData;

static void freq_reinit(void *ud){
    UserData *udata = ud;
    udata->osc->freq = 500 + ut_rand(udata->ut) % 2000;
}

static void freq_compute(void *ud, UTFLOAT *out){
    UserData *udata = ud;
    *out = udata->osc->freq;
}

int t_maygate(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT trig = 0;
    UTFLOAT env = 0;
    UTFLOAT osc = 0;
    UTFLOAT mgate = 0;
    
    ut_srand(ut, 123456);
    UserData ud;
    ud.freq = 400;
    ud.ut = ut; 
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
    ut_tevent_init(ut, ud.te, freq_reinit, freq_compute, &ud);
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);


    for(n = 0; n < tst->size; n++) {
        trig = 0;
        env = 0;
        osc = 0;
        mgate = 0;
        ut_metro_compute(ut, ud.met, NULL, &trig);
        ut_maygate_compute(ut, ud.mg, &trig, &mgate);
        ut_tevent_compute(ut, ud.te, &trig, &ud.osc->freq);
        ut_tenv_compute(ut, ud.tenv, &trig, &env);
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut->out[0] = osc * env * mgate;
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_maygate_destroy(&ud.mg);
    ut_tenv_destroy(&ud.tenv);
    ut_metro_destroy(&ud.met);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_tevent_destroy(&ud.te);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
