#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_metro *met;
    ut_nsmp *nsmp;
    ut_ftbl *ft;
} UserData;

int t_nsmp(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT met = 0, nsmp = 0;
    ut_srand(ut, 1234567);
    UserData ud;

    ut_ftbl_loadfile(ut, &ud.ft, SAMPDIR "oneart.wav");
    ut_nsmp_create(&ud.nsmp);
    ut_metro_create(&ud.met);

    ut_metro_init(ut, ud.met);
    ud.met->freq = 2;
    ut_nsmp_init(ut, ud.nsmp, ud.ft, 44100, SAMPDIR "oneart.ini");

    for(n = 0; n < tst->size; n++) {
        met = 0; nsmp = 0;
        ut_metro_compute(ut, ud.met, NULL, &met);
        if(met) {
            ud.nsmp->index = ut_rand(ut) % 3;
        }
        ut_nsmp_compute(ut, ud.nsmp, &met, &nsmp);
        ut_test_add_sample(tst, nsmp);
    }

    fail = ut_test_verify(tst, hash);

    ut_nsmp_destroy(&ud.nsmp);
    ut_metro_destroy(&ud.met);

    ut_ftbl_destroy(&ud.ft);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
