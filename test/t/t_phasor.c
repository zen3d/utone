#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_phasor *phs;
} UserData;

int t_phasor(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;

    UserData ud;
    ut_phasor_create(&ud.phs);
    ut_phasor_init(ut, ud.phs, 0);

    for(n = 0; n < tst->size; n++) {
        ut_phasor_compute(ut, ud.phs, NULL, &ut->out[0]);
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_phasor_destroy(&ud.phs);
     
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
