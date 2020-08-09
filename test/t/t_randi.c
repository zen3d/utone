#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_osc *osc;
    ut_ftbl *ft; 
    ut_randi *rnd;
} UserData;

int t_randi(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT freq;
    
    UserData ud;
    ut_srand(ut, 12345);
    ut_ftbl_create(ut, &ud.ft, 1024);
    ut_osc_create(&ud.osc);
    ut_randi_create(&ud.rnd);

    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ut_randi_init(ut, ud.rnd);
    
    ud.rnd->min = 300;  
    ud.rnd->max = 3000;  

    for(n = 0; n < tst->size; n++) {
        ut_randi_compute(ut, ud.rnd, NULL, &freq);
        ud.osc->freq = freq;
        ut_osc_compute(ut, ud.osc, NULL, &ut->out[0]);
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_randi_destroy(&ud.rnd);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
