#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_saturator *saturator;
    ut_osc *osc;
    ut_ftbl *ft;
} UserData;

int t_saturator(ut_test *tst, ut_data *ut, const char *hash)
{
    ut_srand(ut, 12345);
    uint32_t n;
    int fail = 0;
    UserData ud;
        UTFLOAT osc = 0, saturator = 0;

    ut_saturator_create(&ud.saturator);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_saturator_init(ut, ud.saturator);
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->amp = 0.5;
    ud.saturator->dcoffset = 4;
    ud.saturator->drive = 20;
    ut->len = 44100 * 5;

    for(n = 0; n < tst->size; n++) {
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut_saturator_compute(ut, ud.saturator, &osc, &saturator);
        ut_test_add_sample(tst, saturator);
    }

    fail = ut_test_verify(tst, hash);

    ut_saturator_destroy(&ud.saturator);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
