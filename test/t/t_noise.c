#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_noise *ns;
} UserData;

int t_noise(ut_test *tst, ut_data *ut, const char *hash) 
{
    ut_srand(ut, 0); 
    uint32_t n;
    int fail = 0;

    UserData ud;
    ut_noise_create(&ud.ns);
    ut_noise_init(ut, ud.ns);

    UTFLOAT in;

    for(n = 0; n < tst->size; n++) {
        ut_noise_compute(ut, ud.ns, &in, &ut->out[0]); 
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_noise_destroy(&ud.ns);
    
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
