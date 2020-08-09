#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

int t_allpass(ut_test *tst, ut_data *ut, const char *hash) 
{
    ut_srand(ut, 0); 
    uint32_t n;
    int fail = 0;
    ut_allpass *ap_d;
    ut_tenv *env_d;
    ut_noise *nz_d;

    UTFLOAT tick = 0, env = 0, noise = 0, allpass = 0;

    ut_allpass_create(&ap_d);
    ut_tenv_create(&env_d);
    ut_noise_create(&nz_d);

    ut_allpass_init(ut, ap_d, 0.1);
    ut_tenv_init(ut, env_d);
    env_d->atk = 0.001;
    env_d->hold = 0.00;
    env_d->rel =  0.1;

    ut_noise_init(ut, nz_d);

    for(n = 0; n < tst->size; n++) {

        tick = 0, env = 0, noise = 0, allpass = 0;
        tick = (n == 0) ? 1 : 0;
        ut_tenv_compute(ut, env_d, &tick, &env);
        ut_noise_compute(ut, nz_d, NULL, &noise);
        noise *= env * 0.5;
        ut_allpass_compute(ut, ap_d, &noise, &allpass);

        ut_test_add_sample(tst, allpass);
    }

    fail = ut_test_verify(tst,hash);

    ut_noise_destroy(&nz_d);
    ut_tenv_destroy(&env_d);
    ut_allpass_destroy(&ap_d);
     
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
