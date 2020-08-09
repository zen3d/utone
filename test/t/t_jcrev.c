#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_fosc *osc;
    ut_ftbl *ft; 
    ut_jcrev *ut;
    int counter;
} UserData;

int t_jcrev(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UserData ud;
    UTFLOAT in = 0, out = 0;

    ut_srand(ut, 123456);
    ut_jcrev_create(&ud.ut);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_fosc_create(&ud.osc);

    ut_jcrev_init(ut, ud.ut);
    ud.counter = 0;
    ut_gen_sine(ut, ud.ft);
    ut_fosc_init(ut, ud.osc, ud.ft);
    ud.osc->freq = 500;

    for(n = 0; n < tst->size; n++) {
        in = 0, out = 0;

        if(ud.counter == 0){
            ud.osc->freq = 500 + ut_rand(ut) % 2000;
        }

        ut_fosc_compute(ut, ud.osc, NULL, &in);
        ut_jcrev_compute(ut, ud.ut, &in, &out);

        ut->out[0] = out;
        ud.counter = (ud.counter + 1) % 4410;
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);
    
    ut_jcrev_destroy(&ud.ut);
    ut_ftbl_destroy(&ud.ft);
    ut_fosc_destroy(&ud.osc);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
