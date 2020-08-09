#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_delay *delay;
    ut_osc *osc;
    ut_metro *met;
    ut_tenv *tenv;
    ut_ftbl *ft;
} UserData;

int t_delay(ut_test *tst, ut_data *ut, const char *hash) 
{
    ut_srand(ut, 0);
    uint32_t n;
    int fail = 0;
    UTFLOAT osc = 0, delay = 0, met = 0, tenv = 0;
    UserData ud;

    ut_delay_create(&ud.delay);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_metro_create(&ud.met);
    ut_tenv_create(&ud.tenv);

    ut_delay_init(ut, ud.delay, 0.75 * 0.5);
    ud.delay->feedback = 0.5;
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
        osc = 0, delay = 0, met = 0, tenv = 0;
        ut_metro_compute(ut, ud.met, NULL, &met);
        ut_tenv_compute(ut, ud.tenv, &met, &tenv);
        if(met) {
            ud.osc->freq = 100 + ut_rand(ut) % 500;
        }
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        osc *= tenv;
        ut_delay_compute(ut, ud.delay, &osc, &delay);

        ut_test_add_sample(tst, osc + delay);
    }

    fail = ut_test_verify(tst, hash);
    
    ut_metro_destroy(&ud.met);
    ut_delay_destroy(&ud.delay);
    ut_osc_destroy(&ud.osc);
    ut_ftbl_destroy(&ud.ft);
    ut_tenv_destroy(&ud.tenv);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
