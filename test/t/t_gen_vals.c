#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

int t_gen_vals(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT out = 0;

    ut_ftbl *ft;
    ut_ftbl_create(ut, &ft, 4096);
    ut_gen_sinesum(ut, ft, "1 1.5 -3 5 ");

    for(n = 0; n < tst->size; n++) {
        if(n < ft->size) {
            out = ft->tbl[n];
        } else {
            out = 0;
        }
        ut_test_add_sample(tst, out);
    }

    fail = ut_test_verify(tst, hash);

    ut_ftbl_destroy(&ft);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
