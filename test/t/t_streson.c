#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_noise *ns;
    ut_streson *stres;
} UserData;

int t_streson(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT noise = 0;

    ut_srand(ut, 123456);
    UserData ud;

    ut_streson_create(&ud.stres);
    ut_noise_create(&ud.ns);
    ut_noise_init(ut, ud.ns);
    ut_streson_init(ut, ud.stres);
    ut->len = 44100 * 5;

    for(n = 0; n < tst->size; n++) {
        noise = 0;
        ut_noise_compute(ut, ud.ns, NULL, &noise);
        ut_streson_compute(ut, ud.stres, &noise, &ut->out[0]);
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);
    
    ut_noise_destroy(&ud.ns);
    ut_streson_destroy(&ud.stres);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
