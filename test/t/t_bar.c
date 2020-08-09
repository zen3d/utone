#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_bar *bar;
    ut_metro *met;
} UserData;

int t_bar(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT bar = 0, met = 0;
    ut_srand(ut, 1234567);
    UserData ud;

    ut_bar_create(&ud.bar);
    ut_metro_create(&ud.met);

    ut_bar_init(ut, ud.bar, 3, 0.0001);
    ud.bar->T30 = 1;

    ut_metro_init(ut, ud.met);
    ud.met->freq = 1;

    for(n = 0; n < tst->size; n++) {
        bar = 0; 
        met = 0;
        ut_metro_compute(ut, ud.met, NULL, &met);
        ut_bar_compute(ut, ud.bar, &met, &bar);
        ut_test_add_sample(tst, bar);
    }

    fail = ut_test_verify(tst, hash);

    ut_bar_destroy(&ud.bar);
    ut_metro_destroy(&ud.met);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
