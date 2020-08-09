#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_tseg *tseg;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

int t_tseg(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    ut_srand(ut, 1234567);
    UserData ud;
    UTFLOAT osc = 0, tseg = 0;
    UTFLOAT trig = (ut->pos == 0);

    ut_tseg_create(&ud.tseg);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_tseg_init(ut, ud.tseg, 0.0001);
    ud.tseg->end = 1.0;
    ud.tseg->type = 3.0;
    ud.tseg->dur = 4.0;

    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);

    for(n = 0; n < tst->size; n++) {
        osc = 0; 
        tseg = 0;
        trig = (ut->pos == 0);
        ut_tseg_compute(ut, ud.tseg, &trig, &tseg);
        ud.osc->freq = 100 + (tseg * 1000);
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut_test_add_sample(tst, osc);
    }

    fail = ut_test_verify(tst, hash);

    ut_tseg_destroy(&ud.tseg);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
