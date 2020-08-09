#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_osc *osc;
    ut_ftbl *ft;
    ut_metro *met;
    ut_tenv *tenv;
    UTFLOAT freq;
} UserData;

int t_tenv(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;

    UserData ud;
    ut_srand(ut, 123456);

    ut_tenv_create(&ud.tenv);
    ut_metro_create(&ud.met);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_osc_create(&ud.osc);

    ut_tenv_init(ut, ud.tenv);
    ud.tenv->atk = 0.03;
    ud.tenv->hold = 0.01;
    ud.tenv->rel = 0.1;
    ut_metro_init(ut, ud.met);
    ud.met->freq = 3;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);

    for(n = 0; n < tst->size; n++) {
        UTFLOAT trig = 0;
        UTFLOAT env = 0;
        UTFLOAT osc = 0;
        ut_metro_compute(ut, ud.met, NULL, &trig);
        if(trig) ud.osc->freq = 500 + ut_rand(ut) % 2000;
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut_tenv_compute(ut, ud.tenv, &trig, &env);
        ut->out[0] = osc * env;
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_tenv_destroy(&ud.tenv);
    ut_metro_destroy(&ud.met);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
