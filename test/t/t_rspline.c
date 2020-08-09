#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_rspline *spline;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

int t_rspline(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT osc, spline;

    UserData ud;
    ut_srand(ut, 1234567);
    
    ut_rspline_create(&ud.spline);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_rspline_init(ut, ud.spline);
    ud.spline->min = 300;
    ud.spline->max = 900;
    ud.spline->cps_min = 0.1;
    ud.spline->cps_max = 3;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);

    for(n = 0; n < tst->size; n++) {
        /* compute samples and add to test buffer */
        osc = 0; 
        spline = 0;
        ut_rspline_compute(ut, ud.spline, NULL, &spline);
        ud.osc->freq = spline;
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut_test_add_sample(tst, osc);
    }

    fail = ut_test_verify(tst, hash);
    
    ut_rspline_destroy(&ud.spline);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
