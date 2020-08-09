#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_osc *osc1;
    ut_osc *osc2;
    ut_ftbl *ft;
    ut_metro *met;
    ut_tenv *tenv1;
    ut_tenv *tenv2;
    ut_tdiv *tdiv;
} UserData;

int t_tdiv(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;

    UTFLOAT trig = 0;
    UTFLOAT div  = 0;
    UTFLOAT env1 = 0;
    UTFLOAT env2 = 0;
    UTFLOAT osc1 = 0;
    UTFLOAT osc2 = 0;

    UserData ud;
    ut_srand(ut, 123456);

    ut_tenv_create(&ud.tenv1);
    ut_tenv_create(&ud.tenv2);
    ut_metro_create(&ud.met);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_osc_create(&ud.osc1);
    ut_osc_create(&ud.osc2);
    ut_tdiv_create(&ud.tdiv);

    ut_tenv_init(ut, ud.tenv1);
    ud.tenv1->atk = 0.03;
    ud.tenv1->hold = 0.01;
    ud.tenv1->rel = 0.1;

    ut_tenv_init(ut, ud.tenv2);
    ud.tenv2->atk = 0.03;
    ud.tenv2->hold = 0.01;
    ud.tenv2->rel = 0.1;

    ut_metro_init(ut, ud.met);
    ud.met->freq = 3;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc1, ud.ft, 0);
    ud.osc1->freq = 400; 
    ut_osc_init(ut, ud.osc2, ud.ft, 0);
    ud.osc2->freq = 800; 
    
    ut_tdiv_init(ut, ud.tdiv);
    ud.tdiv->num = 3;

    for(n = 0; n < tst->size; n++) {
        trig = 0;
        div  = 0;
        env1 = 0;
        env2 = 0;
        osc1 = 0;
        osc2 = 0;
        ut_metro_compute(ut, ud.met, NULL, &trig);
        ut_tdiv_compute(ut, ud.tdiv, &trig, &div);
        ut_osc_compute(ut, ud.osc1, NULL, &osc1);
        ut_osc_compute(ut, ud.osc2, NULL, &osc2);

        ut_tenv_compute(ut, ud.tenv1, &trig, &env1);
        ut_tenv_compute(ut, ud.tenv2, &div, &env2);

        ut->out[0] = (osc1 * env1) + (osc2 * env2);
        ut_test_add_sample(tst, 0);
    }

    fail = ut_test_verify(tst, hash);

    ut_tenv_destroy(&ud.tenv1);
    ut_tenv_destroy(&ud.tenv2);
    ut_metro_destroy(&ud.met);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc1);
    ut_osc_destroy(&ud.osc2);
    ut_tdiv_destroy(&ud.tdiv);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
