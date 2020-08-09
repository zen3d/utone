#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_sdelay *sdelay;
    ut_lpf18 *filt1;
    ut_lpf18 *filt2;
    ut_metro *met;
} UserData;

int t_sdelay(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT met = 0, sdelay = 0;
    UTFLOAT filt1 = 0, filt2 = 0;

    ut_srand(ut, 1234567);
    UserData ud;

    ut_sdelay_create(&ud.sdelay);
    ut_metro_create(&ud.met);
    ut_lpf18_create(&ud.filt1);
    ut_lpf18_create(&ud.filt2);

    ut_sdelay_init(ut, ud.sdelay, 2000);
    ut_metro_init(ut, ud.met);

    ud.met->freq = 2;

    ut_lpf18_init(ut, ud.filt1);
    ud.filt1->cutoff = 4000;
    ud.filt1->res = 0.8;

    ut_lpf18_init(ut, ud.filt2);
    ud.filt2->cutoff = 500;
    ud.filt2->res = 0.8;

    for(n = 0; n < tst->size; n++) {
        met = 0;
        sdelay = 0;
        filt1 = 0; 
        filt2 = 0;
        ut_metro_compute(ut, ud.met, NULL, &met);
        ut_sdelay_compute(ut, ud.sdelay, &met, &sdelay);

        ut_lpf18_compute(ut, ud.filt1, &met, &filt1);
        ut_lpf18_compute(ut, ud.filt2, &sdelay, &filt2);

        ut->out[0] = filt1 + filt2;
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_sdelay_destroy(&ud.sdelay);
    ut_metro_destroy(&ud.met);
    ut_lpf18_destroy(&ud.filt1);
    ut_lpf18_destroy(&ud.filt2);

    if(fail) return UT_NOT_OK;
    /* fail by default */
    else return UT_OK;
}
