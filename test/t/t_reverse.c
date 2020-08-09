#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_osc *osc;
    ut_ftbl *ft;
    ut_tenv *tenv;
    ut_reverse *rv;
} UserData;

int t_reverse(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    ut_srand(ut, 123456);
    UserData ud; 
    UTFLOAT env = 0;
    UTFLOAT osc = 0;
    UTFLOAT rv = 0;
    UTFLOAT dry = 0;
    UTFLOAT trig;
    
    ut_reverse_create(&ud.rv);
    ut_tenv_create(&ud.tenv);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_osc_create(&ud.osc);

    ut_reverse_init(ut, ud.rv, 1.0);
    ut_tenv_init(ut, ud.tenv);
    ud.tenv->atk = 0.03;
    ud.tenv->hold = 0.01;
    ud.tenv->rel =  0.3;

    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->freq = 1000;
    ud.osc->amp = 0.5;

    /* allocate / initialize modules here */

    for(n = 0; n < tst->size; n++) {
        env = 0;
        osc = 0;
        rv = 0;
        dry = 0;
        trig = 0;

        if(n == 0){
            trig = 1.0;
        }else{
            trig = 0.0;
        }
        ut_tenv_compute(ut, ud.tenv, &trig, &env);
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        dry = osc * env;
        ut_reverse_compute(ut, ud.rv, &dry, &rv);
        ut->out[0] = dry + rv;
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    /* destroy functions here */
    
    ut_reverse_destroy(&ud.rv);
    ut_tenv_destroy(&ud.tenv);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
