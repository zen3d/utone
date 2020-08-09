#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

int t_atone(ut_test *tst, ut_data *ut, const char *hash) 
{
    ut_srand(ut, 0); 
    uint32_t n;
    int fail = 0;
    UTFLOAT noise = 0, atone = 0;
    
    ut_atone *atone_d;
    ut_noise *noise_d;

    ut_atone_create(&atone_d);
    ut_noise_create(&noise_d);

    ut_atone_init(ut, atone_d);
    ut_noise_init(ut, noise_d);

    for(n = 0; n < tst->size; n++) {
        noise = 0, atone = 0;
        ut_noise_compute(ut, noise_d, NULL, &noise);
        ut_atone_compute(ut, atone_d, &noise, &atone);
        ut_test_add_sample(tst, atone);
    }

    fail = ut_test_verify(tst, hash);

    ut_atone_destroy(&atone_d);
    ut_noise_destroy(&noise_d);
     
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
