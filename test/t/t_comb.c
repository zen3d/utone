#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_comb *comb;
    ut_tenv *env;
    ut_noise *nz;
} UserData; 

int t_comb(ut_test *tst, ut_data *ut, const char *hash) 
{
    ut_srand(ut, 0); 
    uint32_t n;
    int fail = 0;
    UTFLOAT tick = 0, env = 0, noise = 0, comb = 0;
    
    UserData ud;

    ut_comb_create(&ud.comb);
    ut_tenv_create(&ud.env);
    ut_noise_create(&ud.nz);

    ut_comb_init(ut, ud.comb, 0.01);
    ut_tenv_init(ut, ud.env);
    ud.env->atk = 0.001;
    ud.env->hold = 0.00;
    ud.env->rel =  0.1;

    ut_noise_init(ut, ud.nz);

    for(n = 0; n < tst->size; n++) {
        tick = 0, env = 0, noise = 0, comb = 0;

        tick = (ut->pos == 0) ? 1 : 0;
        ut_tenv_compute(ut, ud.env, &tick, &env);
        ut_noise_compute(ut, ud.nz, NULL, &noise);
        noise *= env * 0.5;
        ut_comb_compute(ut, ud.comb, &noise, &comb);
        ut_test_add_sample(tst, comb);
    }

    fail = ut_test_verify(tst, hash);
    
    ut_noise_destroy(&ud.nz);
    ut_tenv_destroy(&ud.env);
    ut_comb_destroy(&ud.comb);
     
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
