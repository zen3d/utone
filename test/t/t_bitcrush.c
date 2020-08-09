#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_bitcrush *bitcrush;
    ut_noise *nz;
} UserData;

int t_bitcrush(ut_test *tst, ut_data *ut, const char *hash)
{
    ut_srand(ut, 0);
    uint32_t n;
    int fail = 0;
    UTFLOAT noise = 0, bitcrush = 0;
    UserData ud;

    ut_bitcrush_create(&ud.bitcrush);
    ut_noise_create(&ud.nz);

    ut_noise_init(ut, ud.nz);
    ut_bitcrush_init(ut, ud.bitcrush);
    ud.bitcrush->bitdepth = 8;
    ud.bitcrush->srate = 10000;

    for(n = 0; n < tst->size; n++) {
        noise = 0, bitcrush = 0;
        ut_noise_compute(ut, ud.nz, NULL, &noise);
        ut_bitcrush_compute(ut, ud.bitcrush, &noise, &bitcrush);
        ut_test_add_sample(tst, bitcrush);
    }

    fail = ut_test_verify(tst, hash);

    ut_bitcrush_destroy(&ud.bitcrush);
    ut_noise_destroy(&ud.nz);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
