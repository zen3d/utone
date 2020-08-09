#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_thresh *thresh;
    ut_osc *osc, *lfo;
    ut_ftbl *ft; 
    ut_tenv *tenv;
} UserData;

int t_thresh(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;

    ut_srand(ut, 1234567);
    UserData ud;
    UTFLOAT osc = 0, thresh = 0, lfo = 0, tenv = 0;

    ut_thresh_create(&ud.thresh);
    ut_osc_create(&ud.osc);
    ut_osc_create(&ud.lfo);
    ut_tenv_create(&ud.tenv);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_thresh_init(ut, ud.thresh);
    ud.thresh->mode = 1;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);

    ut_osc_init(ut, ud.lfo, ud.ft, 0);
    ud.lfo->freq = 3;
    ud.lfo->amp = 1;

    ut_tenv_init(ut, ud.tenv);
    ud.tenv->atk = 0.01;
    ud.tenv->hold = 0.01;
    ud.tenv->rel = 0.01;

    for(n = 0; n < tst->size; n++) {
        osc = 0; thresh = 0; lfo = 0; tenv = 0;
        ut_osc_compute(ut, ud.lfo, NULL, &lfo);
        ut_thresh_compute(ut, ud.thresh, &lfo, &thresh);
        ut_tenv_compute(ut, ud.tenv, &thresh, &tenv);
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut_test_add_sample(tst, osc * tenv);
    }

    fail = ut_test_verify(tst, hash);

    ut_thresh_destroy(&ud.thresh);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_osc_destroy(&ud.lfo);
    ut_tenv_destroy(&ud.tenv);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
