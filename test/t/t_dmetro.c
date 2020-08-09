#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_dmetro *dmetro;
    ut_osc *osc;
    ut_osc *lfo;
    ut_ftbl *ft;
    ut_tenv *tenv;
} UserData;

int t_dmetro(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UserData ud;
    UTFLOAT osc = 0, dmetro = 0, tenv = 0, lfo = 0;
    
    ut_dmetro_create(&ud.dmetro);
    ut_osc_create(&ud.osc);
    ut_osc_create(&ud.lfo);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_tenv_create(&ud.tenv);

    ut_dmetro_init(ut, ud.dmetro);
    ud.dmetro->time = 0.05;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ut_osc_init(ut, ud.lfo, ud.ft, 0);
    ud.lfo->freq = 0.3;
    ud.lfo->amp = 0.5;
    ut_tenv_init(ut, ud.tenv);
    ud.tenv->atk = 0.001;
    ud.tenv->hold = 0.03;
    ud.tenv->rel =  0.001;

    for(n = 0; n < tst->size; n++) {
        osc = 0, dmetro = 0, tenv = 0, lfo = 0;
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut_osc_compute(ut, ud.lfo, NULL, &lfo);
        lfo += 0.5;
        ud.dmetro->time = 0.05 + 0.3 * lfo;
        ut_dmetro_compute(ut, ud.dmetro, NULL, &dmetro);
        ut_tenv_compute(ut, ud.tenv, &dmetro, &tenv);
        ut_test_add_sample(tst, tenv * osc);
    }

    fail = ut_test_verify(tst, hash);
    
    ut_dmetro_destroy(&ud.dmetro);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_osc_destroy(&ud.lfo);
    ut_tenv_destroy(&ud.tenv);
     
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
