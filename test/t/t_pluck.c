#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_pluck *pluck;
    ut_metro *met;
} UserData;

int t_pluck(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;

    UserData ud;
    ut_srand(ut, 1337); 
    UTFLOAT pluck = 0, met = 0;
    UTFLOAT notes[] = {60, 63, 67, 70, 74};

    ut_pluck_create(&ud.pluck);
    ut_metro_create(&ud.met);

    ut_pluck_init(ut, ud.pluck, 400);
    ut_metro_init(ut, ud.met);
    ud.met->freq = 4;

    for(n = 0; n < tst->size; n++) {
        pluck = 0, met = 0;
        ut_metro_compute(ut, ud.met, NULL, &met);
        if(met) {
            ud.pluck->freq = ut_midi2cps(notes[ut_rand(ut) % 5]);
        }
        ut_pluck_compute(ut, ud.pluck, &met, &pluck);
        ut_test_add_sample(tst, pluck);
    }
    
    fail = ut_test_verify(tst, hash);

    ut_pluck_destroy(&ud.pluck);
    ut_metro_destroy(&ud.met);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
