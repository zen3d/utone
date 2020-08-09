#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_hilbert *hilbert;
    ut_osc *cos, *sin;
    ut_ftbl *ft; 
    ut_diskin *diskin;
} UserData;

int t_hilbert(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT real = 0, imag = 0;
    UTFLOAT diskin = 0;
    UTFLOAT sin = 0, cos = 0;

    ut_srand(ut, 1234567);
    UserData ud;

    ut_hilbert_create(&ud.hilbert);
    ut_osc_create(&ud.sin);
    ut_osc_create(&ud.cos);
    ut_diskin_create(&ud.diskin);
    ut_ftbl_create(ut, &ud.ft, 8192);

    ut_hilbert_init(ut, ud.hilbert);
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.sin, ud.ft, 0);
    ut_osc_init(ut, ud.cos, ud.ft, 0.25);
    ud.sin->freq = 1000;
    ud.cos->freq = 1000;
    ut_diskin_init(ut, ud.diskin, SAMPDIR "oneart.wav");

    for(n = 0; n < tst->size; n++) {
        real = 0; 
        imag = 0;
        diskin = 0;
        sin = 0; 
        cos = 0;

        ut_diskin_compute(ut, ud.diskin, NULL, &diskin);
        ut_osc_compute(ut, ud.sin, NULL, &sin);
        ut_osc_compute(ut, ud.cos, NULL, &cos);
        ut_hilbert_compute(ut, ud.hilbert, &diskin, &real, &imag);
        ut->out[0] = ((cos * real) + (sin * real)) * 0.7;
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_hilbert_destroy(&ud.hilbert);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.sin);
    ut_osc_destroy(&ud.cos);
    ut_diskin_destroy(&ud.diskin);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
