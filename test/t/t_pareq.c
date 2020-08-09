#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_pareq *pareq;
    ut_noise *noise;
    ut_ftbl *ft; 
} UserData;

int t_pareq(ut_test *tst, ut_data *ut, const char *hash) 
{
    ut_srand(ut, 0); 
    uint32_t n;
    int fail = 0;

    UserData ud;

    ut_pareq_create(&ud.pareq);
    ut_noise_create(&ud.noise);

    ut_pareq_init(ut, ud.pareq);
    ud.pareq->fc = 500;
    ut_noise_init(ut, ud.noise);
    ud.noise->amp = 0.4;

    for(n = 0; n < tst->size; n++) {
        UTFLOAT noise = 0, pareq = 0;
        ut_noise_compute(ut, ud.noise, NULL, &noise);
        ut_pareq_compute(ut, ud.pareq, &noise, &pareq);
        ut->out[0] = pareq;
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_pareq_destroy(&ud.pareq);
    ut_noise_destroy(&ud.noise);
 
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
