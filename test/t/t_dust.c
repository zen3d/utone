#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_dust *dst;
} UserData;

int t_dust(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT out = 0;
    UserData ud;
    
    ut_dust_create(&ud.dst);
    ut_dust_init(ut, ud.dst);
    ut->len = 44100 * 5;
    ud.dst->bipolar = 1.0;

    for(n = 0; n < tst->size; n++) {
        out = 0;
        ut_dust_compute(ut, ud.dst, NULL, &out);
        ut_test_add_sample(tst, out);
    }

    fail = ut_test_verify(tst, hash);

    ut_dust_destroy(&ud.dst);
     
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
