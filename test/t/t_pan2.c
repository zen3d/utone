#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_pan2 *pan2;
    ut_osc *osc;
    ut_osc *lfo;
    ut_ftbl *ft; 
} UserData;

int t_pan2(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT osc = 0, outL = 0, outR = 0, lfo = 0;

    UserData ud;

    ut_pan2_create(&ud.pan2);
    ut_osc_create(&ud.osc);
    ut_osc_create(&ud.lfo);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_pan2_init(ut, ud.pan2);
    ud.pan2->type = 2;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ut_osc_init(ut, ud.lfo, ud.ft, 0);
    ud.lfo->amp = 1;
    ud.lfo->freq = 1;

    for(n = 0; n < tst->size; n++) {
        osc = 0; outL = 0; outR = 0; lfo = 0;
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut_osc_compute(ut, ud.lfo, NULL, &lfo);
        ud.pan2->pan = lfo;
        ut_pan2_compute(ut, ud.pan2, &osc, &outL, &outR);
        ut_test_add_sample(tst, outL);
    }

    fail = ut_test_verify(tst, hash);

    ut_pan2_destroy(&ud.pan2);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_osc_destroy(&ud.lfo);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
