#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_ptrack *ptrack;
    ut_osc *osc;
    ut_ftbl *ft;
    ut_blsaw *blsaw;
    ut_randh *randh;
} UserData;

int t_ptrack(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT freq = 0, amp = 0, blsaw = 0, randh = 0, osc = 0;

    UserData ud;
    ut_srand(ut, 1234567);

    ut_ptrack_create(&ud.ptrack);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_blsaw_create(&ud.blsaw);
    ut_randh_create(&ud.randh);

    ut_ptrack_init(ut, ud.ptrack, 512, 20);
    ut_randh_init(ut, ud.randh);
    ud.randh->max = 500;
    ud.randh->min = 200;
    ud.randh->freq = 6;

    ut_blsaw_init(ut, ud.blsaw);
    *ud.blsaw->amp = 1.0;

    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);


    for(n = 0; n < tst->size; n++) {
        freq = 0; amp = 0; blsaw = 0; randh = 0; osc = 0;
        ut_randh_compute(ut, ud.randh, NULL, &randh);
        *ud.blsaw->freq = randh;
        ut_blsaw_compute(ut, ud.blsaw, NULL, &blsaw);
        ut_ptrack_compute(ut, ud.ptrack, &blsaw, &freq, &amp);
        ud.osc->freq = freq;
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut_test_add_sample(tst, osc);
    }

    fail = ut_test_verify(tst, hash);

    ut_blsaw_destroy(&ud.blsaw);
    ut_randh_destroy(&ud.randh);
    ut_ptrack_destroy(&ud.ptrack);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
