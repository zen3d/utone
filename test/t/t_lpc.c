#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_uta *wav;
    ut_lpc *lpc;
} user_data;

int t_lpc(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    user_data dt;
    UTFLOAT diskin;
    UTFLOAT out;

    diskin = 0;
    out = 0;
    ut_lpc_create(&dt.lpc);
    ut_lpc_init(ut, dt.lpc, 512);
    ut_uta_create(&dt.wav);
    ut_uta_init(ut, dt.wav, SAMPDIR "oneart.uta");


    for(n = 0; n < tst->size; n++) {
        ut_uta_compute(ut, dt.wav, NULL, &diskin);
        ut_lpc_compute(ut, dt.lpc, &diskin, &out);

        ut_test_add_sample(tst, out);
    }

    fail = ut_test_verify(tst, hash);

    ut_uta_destroy(&dt.wav);
    ut_lpc_destroy(&dt.lpc);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
