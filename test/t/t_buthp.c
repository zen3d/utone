#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_noise *ns;
    ut_buthp *buthp;
} UserData;

int t_buthp(ut_test *tst, ut_data *ut, const char *hash) 
{
    ut_srand(ut, 0); 
    uint32_t n;
    int fail = 0;
    UTFLOAT in = 0;
    UTFLOAT out = 0;
    
    UserData ud;
    ut_noise_create(&ud.ns);
    ut_buthp_create(&ud.buthp);
    ut_noise_init(ut, ud.ns);
    ut_buthp_init(ut, ud.buthp);
    ud.buthp->freq = 5000;

    for(n = 0; n < tst->size; n++) {
        in = 0;
        out = 0;
        ut_noise_compute(ut, ud.ns, NULL, &in);
        ut_buthp_compute(ut, ud.buthp, &in, &out); 
        ut_test_add_sample(tst, out);
    }
    
    fail = ut_test_verify(tst, hash);
    
    ut_noise_destroy(&ud.ns);
    ut_buthp_destroy(&ud.buthp);
     
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
