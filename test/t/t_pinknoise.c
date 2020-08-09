#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_pinknoise *ns;
} UserData;

int t_pinknoise(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT out = 0;

    UserData ud;
    ut_srand(ut, 12345);
    ut_pinknoise_create(&ud.ns);
    ut_pinknoise_init(ut, ud.ns);

    for(n = 0; n < tst->size; n++) {
        out = 0;
        ut_pinknoise_compute(ut, ud.ns, NULL, &out);
        ut_test_add_sample(tst, out);
    }

    fail = ut_test_verify(tst, hash);

    ut_pinknoise_destroy(&ud.ns);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
