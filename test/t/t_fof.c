#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_fof *fof;
    ut_ftbl *sine;
    ut_ftbl *win;
} UserData;

int t_fof(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT osc = 0, fof = 0;

    ut_srand(ut, 1234567);
    UserData ud;

    ut_ftbl_create(ut, &ud.sine, 2048);
    ut_ftbl_create(ut, &ud.win, 1024);
    ut_fof_create(&ud.fof);

    ut_gen_sine(ut, ud.sine);
    ut_gen_composite(ut, ud.win, "0.5 0.5 270 0.5");

    ut_fof_init(ut, ud.fof, ud.sine, ud.win, 100, 0);

    for(n = 0; n < tst->size; n++) {
        osc = 0;
        fof = 0;
        ut_fof_compute(ut, ud.fof, &osc, &fof);
        ut_test_add_sample(tst, fof);
    }

    fail = ut_test_verify(tst, hash);
    
    ut_fof_destroy(&ud.fof);
    ut_ftbl_destroy(&ud.sine);
    ut_ftbl_destroy(&ud.win);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
