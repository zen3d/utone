#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_drip *drip;
    ut_dust *trig;
    ut_revsc *rev;
} UserData;

int t_drip(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT trig, rev1, rev2, drip;
    UserData ud;

    ut_revsc_create(&ud.rev);
    ut_drip_create(&ud.drip);
    ut_dust_create(&ud.trig);
    
    ut_dust_init(ut, ud.trig);
    ut_drip_init(ut, ud.drip, 0.09);
    ud.drip->amp = 0.3;
    ut_revsc_init(ut, ud.rev);
    ud.rev->feedback = 0.9;
    
    for(n = 0; n < tst->size; n++) {
        ut_dust_compute(ut, ud.trig, NULL, &trig);
        ut_drip_compute(ut, ud.drip, &trig, &drip);
        ut_revsc_compute(ut, ud.rev, &drip, &drip, &rev1, &rev2);
        ut_test_add_sample(tst, drip + rev1 * 0.05);
    }

    fail = ut_test_verify(tst, hash);
    
    ut_drip_destroy(&ud.drip);
    ut_dust_destroy(&ud.trig);
    ut_revsc_destroy(&ud.rev);
     
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
