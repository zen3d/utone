#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_tenv2 *tenv2;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

int t_tenv2(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    ut_srand(ut, 1234567);
    UserData ud;
    UTFLOAT osc = 0, tenv2 = 0, tick = 0;

    ut_tenv2_create(&ud.tenv2);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_tenv2_init(ut, ud.tenv2);
    ud.tenv2->atk = 3;
    ud.tenv2->rel = 1;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->amp = 0.6;

    for(n = 0; n < tst->size; n++) {
        osc = 0, tenv2 = 0, tick = 0;

        if(ut->pos == 0 || ut->pos == ut->sr * 1) tick = 1;

        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut_tenv2_compute(ut, ud.tenv2, &tick, &tenv2);
        ut->out[0] = osc * tenv2;
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);
    
    ut_tenv2_destroy(&ud.tenv2);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
