#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_waveset *waveset;
    ut_diskin *diskin;
} UserData;

int t_waveset(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT wav = 0, waveset = 0;

    UserData ud;
    ut_srand(ut, 1234567);

    ut_waveset_create(&ud.waveset);
    ut_diskin_create(&ud.diskin);

    ut_waveset_init(ut, ud.waveset, 1.0);
    ud.waveset->rep = 3.0;
    ut_diskin_init(ut, ud.diskin, SAMPDIR "oneart.wav");

    for(n = 0; n < tst->size; n++) {
        wav = 0; waveset = 0;
        ut_diskin_compute(ut, ud.diskin, NULL, &wav);
        ut_waveset_compute(ut, ud.waveset, &wav, &waveset);
        ut_test_add_sample(tst, waveset);
    }

    fail = ut_test_verify(tst, hash);

    ut_waveset_destroy(&ud.waveset);
    ut_diskin_destroy(&ud.diskin);
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
