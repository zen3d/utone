#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_noise *ns;
    ut_revsc *rev;
    int counter;
} UserData;

int t_revsc(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT in = 0;
    UTFLOAT foo = 0;
    ut_srand(ut, 123456);
    UserData ud;
    ud.counter = 0;
    ut_noise_create(&ud.ns);
    ut_revsc_create(&ud.rev);
    ut_noise_init(ut, ud.ns);
    ut_revsc_init(ut, ud.rev);

    ut->len = 44100 * 5;

    for(n = 0; n < tst->size; n++) {
        in = 0;
        foo = 0;
        ut_noise_compute(ut, ud.ns, NULL, &in);
        
        if(ud.counter < 2000) {
            ud.counter = (ud.counter + 1) % 5000;
        }else{
            in = 0;
        }
        ut_revsc_compute(ut, ud.rev, &in, &in, &ut->out[0], &foo); 
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);
    
    ut_noise_destroy(&ud.ns);
    ut_revsc_destroy(&ud.rev);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
