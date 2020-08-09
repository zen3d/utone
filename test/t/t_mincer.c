#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_mincer *mincer;
    ut_ftbl *ft; 
    ut_randi *randi;
} UserData;

int t_mincer(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT mincer = 0, randi = 0;

    UserData ud;
    ut_srand(ut, 1234567);

    ut_mincer_create(&ud.mincer);
    /* allocates loads an audio file into a ftable */
    ut_ftbl_loadfile(ut, &ud.ft, SAMPDIR "oneart.wav");

    ut_randi_create(&ud.randi);

    ut_mincer_init(ut, ud.mincer, ud.ft, 2048);
    ut_randi_init(ut, ud.randi);
    ud.randi->min = 0;
    ud.randi->max = 5;
    ud.randi->cps = 1;

    for(n = 0; n < tst->size; n++) {
        mincer = 0; randi = 0;
        
        ut_randi_compute(ut, ud.randi, NULL, &randi);
        ud.mincer->time = randi;
        ud.mincer->amp = 1;
        ud.mincer->pitch = 1;
        ut_mincer_compute(ut, ud.mincer, NULL, &mincer);
        ut_test_add_sample(tst, mincer);
    }

    fail = ut_test_verify(tst, hash);

    ut_mincer_destroy(&ud.mincer);
    ut_ftbl_destroy(&ud.ft);
    ut_randi_destroy(&ud.randi);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
