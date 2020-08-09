#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct udata {
    ut_noise *ns;
    ut_biquad *tn;
} UserData;

int t_biquad(ut_test *tst, ut_data *ut, const char *hash) 
{
    ut_srand(ut, 0); 
    uint32_t n;
    int fail = 0;
    UTFLOAT in = 0;
    UTFLOAT out = 0;

    UserData ud;

    ut_noise_create(&ud.ns);
    ut_biquad_create(&ud.tn);

    ut_noise_init(ut, ud.ns);
    ut_biquad_init(ut, ud.tn);

    for(n = 0; n < tst->size; n++) {
        in = 0;
        out = 0;
        ut_noise_compute(ut, ud.ns, NULL, &in);
        ut_biquad_compute(ut, ud.tn, &in, &out); 
        ut_test_add_sample(tst, out);
    }

    fail = ut_test_verify(tst, hash);
    
    ut_noise_destroy(&ud.ns);
    ut_biquad_destroy(&ud.tn);
     
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
