#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_fosc *osc;
    ut_ftbl *ft; 
    int counter;
} UserData;

int t_fosc(ut_test *tst, ut_data *ut, const char *hash) 
{
    ut_srand(ut, 0);
    uint32_t n;
    int fail = 0;
    UserData ud;
    ud.counter = 0;
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_fosc_create(&ud.osc);

    ut_gen_sine(ut, ud.ft);
    ut_fosc_init(ut, ud.osc, ud.ft);
    ud.osc->freq = 500;

    for(n = 0; n < tst->size; n++) {
        if(ud.counter == 0){
            ud.osc->freq = 500 + ut_rand(ut) % 2000;
        }

        ut_fosc_compute(ut, ud.osc, NULL, &ut->out[0]);
        ud.counter = (ud.counter + 1) % 4410;

        ut_test_add_sample(tst, ut->out[0]);
    }


    fail = ut_test_verify(tst, hash);

    ut_ftbl_destroy(&ud.ft);
    ut_fosc_destroy(&ud.osc);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
