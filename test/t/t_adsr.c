#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_adsr *adsr;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

int t_adsr(ut_test *tst, ut_data *ut, const char *hash) 
{
    ut_srand(ut, 12345);
    uint32_t n;
    int fail = 0;
    UserData ud; 
    ut_adsr_create(&ud.adsr);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 8192);
    UTFLOAT osc = 0, adsr = 0, gate = 0;
    

    ut_adsr_init(ut, ud.adsr);
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->amp = 0.5;


    /* allocate / initialize modules here */

    for(n = 0; n < tst->size; n++) {
        if(n < tst->size * 0.5) {
            gate = 1;
        } else {
            gate = 0;
        }
        ut_adsr_compute(ut, ud.adsr, &gate, &adsr);
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut_test_add_sample(tst, adsr * osc);
    }

    fail = ut_test_verify(tst, hash);

    /* destroy functions here */

    ut_adsr_destroy(&ud.adsr);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    if(fail) return UT_NOT_OK;
    /* fail by default */
    else return UT_OK;

}
