#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_brown *brown;
} UserData;

int t_brown(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT brown = 0;

    UserData ud;
    ut_brown_create(&ud.brown);

    ut_brown_init(ut, ud.brown);

    for(n = 0; n < tst->size; n++) {
        ut_brown_compute(ut, ud.brown, NULL, &brown);
        ut_test_add_sample(tst, brown);
    }

    fail = ut_test_verify(tst, hash);
    
    ut_brown_destroy(&ud.brown);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
