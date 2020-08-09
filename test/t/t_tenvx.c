#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_osc *osc;
    ut_ftbl *ft;
    ut_metro *met;
    ut_tenvx *tenvx;
    UTFLOAT freq;
} UserData;

int t_tenvx(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;

    UserData ud;
    UTFLOAT *freqp = &ud.freq;
    ud.freq = 400;
    ut_srand(ut, 123456);

    ut_tenvx_create(&ud.tenvx);
    ut_metro_create(&ud.met);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_osc_create(&ud.osc);

    ut_tenvx_init(ut, ud.tenvx);
    ud.tenvx->atk = 0.03;
    ud.tenvx->hold = 0.1;
    ud.tenvx->rel = 0.1;
    ut_metro_init(ut, ud.met);
    ud.met->freq = 3;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->amp = 0.5;
    ud.osc->freq = *freqp;

    for(n = 0; n < tst->size; n++) {
        UTFLOAT trig = 0;
        UTFLOAT env = 0;
        UTFLOAT osc = 0;
        ut_metro_compute(ut, ud.met, NULL, &trig);
        if(trig) ud.osc->freq = 500 + ut_rand(ut) % 2000;
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut_tenvx_compute(ut, ud.tenvx, &trig, &env);
        ut_test_add_sample(tst, osc * env);
    }

    fail = ut_test_verify(tst, hash);

    ut_tenvx_destroy(&ud.tenvx);
    ut_metro_destroy(&ud.met);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
