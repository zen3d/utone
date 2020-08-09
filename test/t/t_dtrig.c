#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_osc *osc;
    ut_ftbl *ft, *delta;
    ut_tenv *tenv;
    ut_dtrig *dt;
} UserData;

int t_dtrig(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UserData ud;

    UTFLOAT env = 0;
    UTFLOAT osc = 0;
    UTFLOAT trig;
    UTFLOAT dtrig = 0;

    ut_dtrig_create(&ud.dt);
    ut_tenv_create(&ud.tenv);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_ftbl_create(ut, &ud.delta, 4);
    ut_osc_create(&ud.osc);

    ud.delta->tbl[0] = 1.0;
    ud.delta->tbl[1] = 1.0;
    ud.delta->tbl[2] = 0.5;
    ud.delta->tbl[3] = 0.5;
    ut_dtrig_init(ut, ud.dt, ud.delta);
    ut_tenv_init(ut, ud.tenv);
    ud.tenv->atk = 0.03;
    ud.tenv->hold = 0.01;
    ud.tenv->rel =  0.3;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->freq = 1000;
    ud.osc->amp = 0.5;

    for(n = 0; n < tst->size; n++) {
        env = 0;
        osc = 0;
        trig = 0;
        dtrig = 0;
        if(ut->pos == 0){
            trig = 1.0;
        }else{
            trig = 0.0;
        }
        ut_dtrig_compute(ut, ud.dt, &trig, &dtrig);
        ut_tenv_compute(ut, ud.tenv, &dtrig, &env);
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut_test_add_sample(tst, osc * env);
    }
    
    fail = ut_test_verify(tst, hash);
     
    ut_dtrig_destroy(&ud.dt);
    ut_tenv_destroy(&ud.tenv);
    ut_ftbl_destroy(&ud.ft);
    ut_ftbl_destroy(&ud.delta);
    ut_osc_destroy(&ud.osc);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
