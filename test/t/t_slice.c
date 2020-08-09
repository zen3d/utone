#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

int t_slice(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;

    /* allocate / initialize modules here */

    for(n = 0; n < tst->size; n++) {
        /* compute samples and add to test buffer */
        ut_test_add_sample(tst, 0);
    }

    fail = ut_test_verify(tst, hash);

    /* destroy functions here */

    if(fail) return UT_NOT_OK;
    /* fail by default */
    else return UT_NOT_OK;
}
