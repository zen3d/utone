#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_trand *trand;
    ut_metro *met;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

int t_trand(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    
    UserData ud;
    ut_srand(ut, 1234567);

    ut_metro_create(&ud.met);
    ut_trand_create(&ud.trand);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_metro_init(ut, ud.met);
    ud.met->freq = 20;
    ut_trand_init(ut, ud.trand);
    ud.trand->min = 40;
    ud.trand->max = 1000;

    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);

    ut->len = 44100 * 5;  

    for(n = 0; n < tst->size; n++) {
        UTFLOAT osc = 0, trand = 0, met = 0;
        ut_metro_compute(ut, ud.met, NULL, &met);
        ut_trand_compute(ut, ud.trand, &met, &trand);
        ud.osc->freq = trand;
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut->out[0] = osc;
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_trand_destroy(&ud.trand);
    ut_metro_destroy(&ud.met);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
