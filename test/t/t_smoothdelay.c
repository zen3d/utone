#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_smoothdelay *smoothdelay;
    ut_osc *osc;
    ut_metro *met;
    ut_tenv *tenv;
    ut_ftbl *ft;
} UserData;


int t_smoothdelay(ut_test *tst, ut_data *ut, const char *hash) 
{
    ut_srand(ut, 0);
    uint32_t n;
    int fail = 0;
    UTFLOAT osc = 0, smoothdelay = 0, met = 0, tenv = 0;
    UserData ud;

    ut_smoothdelay_create(&ud.smoothdelay);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_metro_create(&ud.met);
    ut_tenv_create(&ud.tenv);

    ut_smoothdelay_init(ut, ud.smoothdelay, 0.75 * 0.5, 256);
    ud.smoothdelay->del = 0.11;
    ud.smoothdelay->feedback = 0.66;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->amp = 0.5;
    ut_metro_init(ut, ud.met);
    ud.met->freq = 1;
    ut_tenv_init(ut, ud.tenv);
    ud.tenv->atk = 0.005;
    ud.tenv->hold = 0.1;
    ud.tenv->rel =  0.1;

    for(n = 0; n < tst->size; n++) {
        osc = 0, smoothdelay = 0, met = 0, tenv = 0;
        ut_metro_compute(ut, ud.met, NULL, &met);
        ut_tenv_compute(ut, ud.tenv, &met, &tenv);
        if(met) {
            ud.osc->freq = 100 + ut_rand(ut) % 500;
        }
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        osc *= tenv;
        ut_smoothdelay_compute(ut, ud.smoothdelay, &osc, &smoothdelay);

        ut_test_add_sample(tst, osc + smoothdelay);
    }

    fail = ut_test_verify(tst, hash);
    
    ut_metro_destroy(&ud.met);
    ut_smoothdelay_destroy(&ud.smoothdelay);
    ut_osc_destroy(&ud.osc);
    ut_ftbl_destroy(&ud.ft);
    ut_tenv_destroy(&ud.tenv);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
