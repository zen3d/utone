#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_fold *fold;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

int t_fold(ut_test *tst, ut_data *ut, const char *hash) 
{
    ut_srand(ut, 0);
    uint32_t n;
    int fail = 0;
    UserData ud;

    ut_fold_create(&ud.fold);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_fold_init(ut, ud.fold);
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);

    ut->len = 44100 * 5;
    for(n = 0; n < tst->size; n++) {
        UTFLOAT osc = 0, fold = 0;
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut_fold_compute(ut, ud.fold, &osc, &fold);
        ut->out[0] = fold;
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_fold_destroy(&ud.fold);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
