#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_diskin *diskin;
    ut_conv *conv;
    ut_ftbl *ft; 
} UserData;

int t_conv(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT conv = 0, diskin = 0; 

    ut_srand(ut, 1234567);
    UserData ud;

    ut_diskin_create(&ud.diskin);
    ut_conv_create(&ud.conv);
    ut_ftbl_loadfile(ut, &ud.ft, SAMPDIR "imp.wav");

    ut_diskin_init(ut, ud.diskin, SAMPDIR "oneart.wav");
    ut_conv_init(ut, ud.conv, ud.ft, 8192);

    for(n = 0; n < tst->size; n++) {
        conv = 0; diskin = 0;
        ut_diskin_compute(ut, ud.diskin, NULL, &diskin);
        ut_conv_compute(ut, ud.conv, &diskin, &conv);
        ut_test_add_sample(tst, 0);
    }

    fail = ut_test_verify(tst, hash);

    ut_conv_destroy(&ud.conv);
    ut_ftbl_destroy(&ud.ft);
    ut_diskin_destroy(&ud.diskin);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
