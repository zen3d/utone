#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_noise *ns;
    ut_fofilt *ff;
} UserData;

int t_fofilt(ut_test *tst, ut_data *ut, const char *hash) 
{
    ut_srand(ut, 0); 
    uint32_t n;
    int fail = 0;
    UTFLOAT in = 0;

    UserData ud;
    ut_noise_create(&ud.ns);
    ut_fofilt_create(&ud.ff);
    ut_noise_init(ut, ud.ns);
    ut_fofilt_init(ut, ud.ff);
    ud.ff->freq = 500;

    for(n = 0; n < tst->size; n++) {
        in = 0;
        ut_noise_compute(ut, ud.ns, NULL, &in);
        ut_fofilt_compute(ut, ud.ff, &in, &ut->out[0]); 
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_noise_destroy(&ud.ns);
    ut_fofilt_destroy(&ud.ff);
 
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
