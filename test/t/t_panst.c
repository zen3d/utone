#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_panst *panst;
    ut_osc *osc;
    ut_osc *lfo;
    ut_ftbl *ft;
} UserData;

int t_panst(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;

    UserData ud;
    UTFLOAT osc = 0, outL = 0, outR = 0, lfo = 0;

    ut_panst_create(&ud.panst);
    ut_osc_create(&ud.osc);
    ut_osc_create(&ud.lfo);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_panst_init(ut, ud.panst);
    ud.panst->type = 0;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ut_osc_init(ut, ud.lfo, ud.ft, 0);
    ud.lfo->amp = 1;
    ud.lfo->freq = 0.5;

    ut->len = 44100 * 5;

    for(n = 0; n < tst->size; n += 2) {
        osc = 0; outL = 0; outR = 0; lfo = 0;

        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut_osc_compute(ut, ud.lfo, NULL, &lfo);
        ud.panst->pan = lfo;

        ut_panst_compute(ut, ud.panst, &osc, &osc, &outL, &outR);
        ut_test_add_sample(tst, outL);
        ut_test_add_sample(tst, outR);
    }

    fail = ut_test_verify(tst, hash);

    ut_panst_destroy(&ud.panst);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_osc_destroy(&ud.lfo);


    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
