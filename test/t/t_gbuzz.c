#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_gbuzz *buzz;
    ut_ftbl *ft; 
    int counter;
} UserData;

int t_gbuzz(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;

    UserData ud;
    ud.counter = 0;
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_gbuzz_create(&ud.buzz);
    ut_gen_sine(ut, ud.ft);
    ut_gbuzz_init(ut, ud.buzz, ud.ft, 0);
 
    for(n = 0; n < tst->size; n++) {
        ut_gbuzz_compute(ut, ud.buzz, NULL, &ut->out[0]);
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_ftbl_destroy(&ud.ft);
    ut_gbuzz_destroy(&ud.buzz);
     
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
