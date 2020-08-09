#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_pshift *pshift;
    ut_diskin *diskin;
} UserData;

int t_pshift(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    ut_srand(ut, 1234567);
    UserData ud;

    UTFLOAT diskin = 0, pshift = 0;

    ut_pshift_create(&ud.pshift);
    ut_diskin_create(&ud.diskin);    

    ut_pshift_init(ut, ud.pshift);
    *ud.pshift->shift = 7;
    *ud.pshift->window = 500;
    /* half window size is smoothest sounding */
    *ud.pshift->xfade = 250;
    ut_diskin_init(ut, ud.diskin, SAMPDIR "oneart.wav");

    for(n = 0; n < tst->size; n++) {
        diskin = 0;
        pshift = 0;
        ut_diskin_compute(ut, ud.diskin, NULL, &diskin);
        ut_pshift_compute(ut, ud.pshift, &diskin, &pshift);
        ut_test_add_sample(tst, pshift);
    }

    fail = ut_test_verify(tst, hash);

    ut_pshift_destroy(&ud.pshift);
    ut_diskin_destroy(&ud.diskin);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
