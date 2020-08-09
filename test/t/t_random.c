#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_random *random;
} UserData;

int t_random(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT random = 0;
    
    ut_srand(ut,1234567);
    UserData ud;
    
    ut_random_create(&ud.random);

    ut_random_init(ut, ud.random);
    ud.random->min = -0.2;
    ud.random->max = 0.2;

    for(n = 0; n < tst->size; n++) {
        /* compute samples and add to test buffer */
        random = 0;
        ut_random_compute(ut, ud.random, NULL, &random);
        ut->out[0] = random;
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    /* destroy functions here */
    ut_random_destroy(&ud.random);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
