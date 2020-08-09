#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_biscale *biscale;
    ut_osc *osc;
    ut_ftbl *ft;
} UserData;

int t_biscale(ut_test *tst, ut_data *ut, const char *hash)
{
    uint32_t n;
    int fail = 0;
    UTFLOAT val = 1;
    UTFLOAT osc = 0, biscale = 0;

    ut_srand(ut, 1234567);
    UserData ud;

    ut_biscale_create(&ud.biscale);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_biscale_init(ut, ud.biscale);
    ud.biscale->min = 0;
    ud.biscale->max = 880;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->amp = 0.1;

    for(n = 0; n < tst->size; n++) {
        osc = 0, biscale = 0;
        /* constant set to 1, when biscaled, it becomes 440 */
        val = 1;
        ut_biscale_compute(ut, ud.biscale, &val, &biscale);
        ud.osc->freq = biscale;
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut->out[0] = osc;
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_biscale_destroy(&ud.biscale);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
