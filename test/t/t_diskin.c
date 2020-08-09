#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_diskin *diskin;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

int t_diskin(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT diskin = 0;

    ut_srand(ut, 1234567);
    UserData ud;

    ut_diskin_create(&ud.diskin);
    ut_diskin_init(ut, ud.diskin, SAMPDIR "oneart.wav");

    for(n = 0; n < tst->size; n++) {
        diskin = 0;
        ut_diskin_compute(ut, ud.diskin, NULL, &diskin);
        ut_test_add_sample(tst, diskin);
    }

    fail = ut_test_verify(tst, hash);

    ut_diskin_destroy(&ud.diskin);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
