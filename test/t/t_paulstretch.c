#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_paulstretch *paulstretch;
    ut_ftbl *ft; 
} UserData;

int t_paulstretch(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT paulstretch = 0;

    ut_srand(ut, 1234567);
    UserData ud;

    ut_paulstretch_create(&ud.paulstretch);
    ut_ftbl_loadfile(ut, &ud.ft, SAMPDIR "oneart.wav");

    ut_paulstretch_init(ut, ud.paulstretch, ud.ft, 1.0, 10);


    for(n = 0; n < tst->size; n++) {
        paulstretch = 0;
        ut_paulstretch_compute(ut, ud.paulstretch, NULL, &paulstretch);
        ut->out[0] = paulstretch;
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_paulstretch_destroy(&ud.paulstretch);
    ut_ftbl_destroy(&ud.ft);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
