#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_butbr *butbr;
    ut_noise *ns;
} UserData;

int t_butbr(ut_test *tst, ut_data *ut, const char *hash) 
{
    ut_srand(ut, 0); 
    uint32_t n;
    int fail = 0;
    UTFLOAT noise = 0, butbr = 0;
    UserData ud;

    ut_butbr_create(&ud.butbr);
    ut_noise_create(&ud.ns);

    ut_butbr_init(ut, ud.butbr);
    ut_noise_init(ut, ud.ns);

    for(n = 0; n < tst->size; n++) {
        noise = 0, butbr = 0;
        ut_noise_compute(ut, ud.ns, NULL, &noise);
        ut_butbr_compute(ut, ud.butbr, &noise, &butbr);
        ut_test_add_sample(tst, butbr);
    }

    fail = ut_test_verify(tst, hash);

    ut_butbr_destroy(&ud.butbr);
    ut_noise_destroy(&ud.ns);
     
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
