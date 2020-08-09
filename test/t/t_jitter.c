#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_fosc *osc;
    ut_ftbl *ft; 
    ut_jitter *jit;
} UserData;

int t_jitter(ut_test *tst, ut_data *ut, const char *hash) 
{
    ut_srand(ut, 1234567);

    uint32_t n;
    int fail = 0;

    UserData ud;
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_fosc_create(&ud.osc);
    ut_jitter_create(&ud.jit);   

    ut_gen_sine(ut, ud.ft);
    ut_fosc_init(ut, ud.osc, ud.ft);
    ut_jitter_init(ut, ud.jit);
    ud.jit->cpsMin = 0.5;
    ud.jit->cpsMax = 4;
    ud.jit->amp = 3;  

    for(n = 0; n < tst->size; n++) {
        UTFLOAT jit = 0;
        ut_jitter_compute(ut, ud.jit, NULL, &jit);
        ud.osc->freq = ut_midi2cps(60 + jit);
        ut_fosc_compute(ut, ud.osc, NULL, &ut->out[0]);
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);
     
    ut_ftbl_destroy(&ud.ft);
    ut_fosc_destroy(&ud.osc);
    ut_jitter_destroy(&ud.jit);
 
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
