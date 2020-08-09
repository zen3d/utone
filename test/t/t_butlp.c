#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_noise *ns;
    ut_butlp *butlp;
    int counter;
} UserData;

int t_butlp(ut_test *tst, ut_data *ut, const char *hash) 
{
    ut_srand(ut, 0); 
    uint32_t n;
    int fail = 0;

    UTFLOAT in = 0;
    UTFLOAT out = 0;
    
    UserData ud;
    ud.counter = 0;
    ut_noise_create(&ud.ns);
    ut_butlp_create(&ud.butlp);
    ut_noise_init(ut, ud.ns);
    ut_butlp_init(ut, ud.butlp);

    for(n = 0; n < tst->size; n++) {
        in = 0;
        out = 0;
        if(ud.counter == 0) {
            ud.butlp->freq= 500 + ut_rand(ut) % 4000;
        }
        ut_noise_compute(ut, ud.ns, NULL, &in);
        ut_butlp_compute(ut, ud.butlp, &in, &out); 
        ud.counter = (ud.counter + 1) % 5000;
        ut_test_add_sample(tst, out);
    }
    
    fail = ut_test_verify(tst, hash);
    
    ut_noise_destroy(&ud.ns);
    ut_butlp_destroy(&ud.butlp);
     
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
