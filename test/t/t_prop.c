#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_prop *prop;
    ut_osc *osc;
    ut_ftbl *ft;
    ut_tenv *tenv;
} UserData;

int t_prop(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT osc = 0, prop = 0, tenv = 0;
    
    ut_srand(ut, 1234567);
    UserData ud;
    
    ut_prop_create(&ud.prop);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_tenv_create(&ud.tenv);

    ut_prop_init(ut, ud.prop, "2(++)3(+++)-2(-2(++))+5(+++++)");
    ud.prop->bpm = 80;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ut_tenv_init(ut, ud.tenv);
    ud.tenv->atk = 0.01;
    ud.tenv->hold = 0.01;
    ud.tenv->rel =  0.2;

    ud.osc->freq = 500;

    for(n = 0; n < tst->size; n++) {

        osc = 0, prop = 0, tenv = 0;
        ud.prop->bpm = 80;
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut_prop_compute(ut, ud.prop, NULL, &prop);
        ut_tenv_compute(ut, ud.tenv, &prop, &tenv);
        ut->out[0] = osc * tenv;
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);
    
    ut_prop_destroy(&ud.prop);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_tenv_destroy(&ud.tenv);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
