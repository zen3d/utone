#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_noise *ns;
    ut_butbp *butbp;
    int counter;
} UserData;

int t_butbp(ut_test *tst, ut_data *ut, const char *hash) 
{
    ut_srand(ut, 0); 
    uint32_t n;
    int fail = 0;
    UTFLOAT in = 0;
    UTFLOAT out = 0;
    UserData ud;
    ud.counter = 0;
    ut_noise_create(&ud.ns);
    ut_butbp_create(&ud.butbp);
    ut_noise_init(ut, ud.ns);
    ut_butbp_init(ut, ud.butbp);

    for(n = 0; n < tst->size; n++) {
        in = 0;
        out = 0;
        if(ud.counter == 0) {
            ud.butbp->freq= 500 + ut_rand(ut) % 4000;
        }
        ut_noise_compute(ut, ud.ns, NULL, &in);
        ut_butbp_compute(ut, ud.butbp, &in, &out); 
        ud.counter = (ud.counter + 1) % 5000;
        ut_test_add_sample(tst, out);
    }

    fail = ut_test_verify(tst, hash);
    
    ut_noise_destroy(&ud.ns);
    ut_butbp_destroy(&ud.butbp);
     
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
