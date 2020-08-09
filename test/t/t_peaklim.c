#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_peaklim *peaklim;
    ut_diskin *diskin;
} UserData;

int t_peaklim(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT diskin = 0, peaklim = 0;

    UserData ud;
    ut_srand(ut, 1234567);

    ut_peaklim_create(&ud.peaklim);
    ut_diskin_create(&ud.diskin);

    ut_peaklim_init(ut, ud.peaklim);
    ud.peaklim->atk = 0.1;
    ud.peaklim->rel = 0.1;
    ud.peaklim->thresh = -30;
    ut_diskin_init(ut, ud.diskin, SAMPDIR "oneart.wav");

    for(n = 0; n < tst->size; n++) {
        diskin = 0; peaklim = 0;
        ut_diskin_compute(ut, ud.diskin, NULL, &diskin);
        ut_peaklim_compute(ut, ud.peaklim, &diskin, &peaklim);
        ut_test_add_sample(tst, peaklim);
    }

    fail = ut_test_verify(tst, hash);

    ut_peaklim_destroy(&ud.peaklim);
    ut_diskin_destroy(&ud.diskin);

    if(fail) return UT_NOT_OK;
    /* fail by default */
    else return UT_OK;
}
