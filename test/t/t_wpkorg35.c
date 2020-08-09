#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_wpkorg35 *wpkorg35;
    ut_noise *noise;
    ut_randi *randi;
} UserData;

int t_wpkorg35(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT noise = 0, wpkorg35 = 0, randi = 0;

    ut_srand(ut, 1234567);
    UserData ud;

    ut_wpkorg35_create(&ud.wpkorg35);
    ut_noise_create(&ud.noise);
    ut_randi_create(&ud.randi);

    ut_wpkorg35_init(ut, ud.wpkorg35);
    ud.wpkorg35->res = 1.99;
    ut_noise_init(ut, ud.noise);
    ud.noise->amp = 0.01;
    ut_randi_init(ut, ud.randi);
    ud.randi->min = 100;
    ud.randi->max = 3000;
    ud.randi->cps = 10;

    for(n = 0; n < tst->size; n++) {
        noise = 0; 
        wpkorg35 = 0; 
        randi = 0;
        ut_randi_compute(ut, ud.randi, NULL, &randi);
        ut_noise_compute(ut, ud.noise, NULL, &noise);
        ud.wpkorg35->cutoff = randi;
        ut_wpkorg35_compute(ut, ud.wpkorg35, &noise, &wpkorg35);
        ut_test_add_sample(tst, wpkorg35);
    }

    fail = ut_test_verify(tst, hash);

    ut_wpkorg35_destroy(&ud.wpkorg35);
    ut_noise_destroy(&ud.noise);
    ut_randi_destroy(&ud.randi);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
