#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_tadsr *tadsr;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

int t_tadsr(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;

    ut_srand(ut, 1234567);
    UserData ud;
    UTFLOAT osc = 0, tadsr = 0, trig = 0;

    ut_tadsr_create(&ud.tadsr);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_tadsr_init(ut, ud.tadsr);
    ud.tadsr->atk = 0.1;
    ud.tadsr->dec = 0.2;
    ud.tadsr->sus = 0.3;
    ud.tadsr->rel = 0.1;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    for(n = 0; n < tst->size; n++) {
        osc = 0; tadsr = 0; trig = 0;
        if(n == 0 || n == ut->sr * 2) trig = 1;
        ut_tadsr_compute(ut, ud.tadsr, &trig, &tadsr);
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut_test_add_sample(tst, 0);
    }

    fail = ut_test_verify(tst, hash);

    ut_tadsr_destroy(&ud.tadsr);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
