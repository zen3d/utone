#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_compressor *compressor;
    ut_diskin *diskin;
} UserData;

int t_compressor(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT diskin = 0, compressor = 0;

    ut_srand(ut, 1234567);
    UserData ud;

    ut_compressor_create(&ud.compressor);
    ut_diskin_create(&ud.diskin);

    ut_compressor_init(ut, ud.compressor);
    *ud.compressor->ratio = 4;
    *ud.compressor->thresh = -30;
    *ud.compressor->atk = 0.2;
    *ud.compressor->rel = 0.2;

    ut_diskin_init(ut, ud.diskin, SAMPDIR "oneart.wav");

    for(n = 0; n < tst->size; n++) {
        diskin = 0; compressor = 0;
        ut_diskin_compute(ut, ud.diskin, NULL, &diskin);
        ut_compressor_compute(ut, ud.compressor, &diskin, &compressor);
        ut_test_add_sample(tst, compressor);
    }

    fail = ut_test_verify(tst, hash);

    ut_compressor_destroy(&ud.compressor);
    ut_diskin_destroy(&ud.diskin);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
