#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_randh *randh;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

int t_randh(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT freq;
    
    UserData ud;
    ut_srand(ut, 12345);
    ut_ftbl_create(ut, &ud.ft, 1024);
    ut_osc_create(&ud.osc);
    ut_randh_create(&ud.randh);

    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ut_randh_init(ut, ud.randh);
    
    ud.randh->min = 300;  
    ud.randh->max = 3000;  

    for(n = 0; n < tst->size; n++) {
        ut_randh_compute(ut, ud.randh, NULL, &freq);
        ud.osc->freq = freq;
        ut_osc_compute(ut, ud.osc, NULL, &ut->out[0]);
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_randh_destroy(&ud.randh);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
