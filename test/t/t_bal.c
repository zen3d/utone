#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

int t_bal(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n, i;
    int fail = 0;
    UTFLOAT out = 0, osc = 0, filt = 0, bal = 0, env = 0, tick;
    
    ut_osc *osc_d[3];
    ut_ftbl *ft_d;
    ut_moogladder *filt_d;
    ut_bal *bal_d;
    ut_tenv *env_d;
    
    ut_ftbl_create(ut, &ft_d, 4096);
    for(i = 0; i < 3; i++) {
        ut_osc_create(&osc_d[i]);
        osc_d[i]->amp = 0.5;
    }
    ut_bal_create(&bal_d);
    ut_moogladder_create(&filt_d);
    filt_d->res = 0.8;
    ut_tenv_create(&env_d);

    ut_gen_line(ut, ft_d, "0 1 4096 -1");
    ut_osc_init(ut, osc_d[0], ft_d, 0);
    osc_d[0]->freq = ut_midi2cps(41 - 0.05);
    ut_osc_init(ut, osc_d[1], ft_d, 0);
    osc_d[1]->freq = ut_midi2cps(41 - 12);
    ut_osc_init(ut, osc_d[2], ft_d, 0);
    osc_d[2]->freq = ut_midi2cps(41 + 0.05);
    ut->len = 44100 * 5;
    ut_bal_init(ut, bal_d);
    ut_moogladder_init(ut, filt_d);
    ut_tenv_init(ut, env_d);
    env_d->atk = 2.25;
    env_d->hold = 0.5;
    env_d->rel =  2.25;


    for(n = 0; n < tst->size; n++) {
        out = 0, osc = 0, filt = 0, bal = 0, env = 0;
        for(i = 0; i < 3; i++) {
           ut_osc_compute(ut, osc_d[i], NULL, &osc);
           out += osc * 0.5;
        }
        tick = (ut->pos == 0) ? 1.0 : 0.0;
        ut_tenv_compute(ut, env_d, &tick, &env);
        filt_d->freq = 300 + 3000 * env;
        ut_moogladder_compute(ut, filt_d, &out, &filt);
        ut_bal_compute(ut, bal_d, &filt, &osc, &bal);
        ut_test_add_sample(tst, bal * env);
    }

    fail = ut_test_verify(tst, hash);
    
    ut_ftbl_destroy(&ft_d);
    for(i = 0; i < 3; i++) ut_osc_destroy(&osc_d[i]);
    ut_bal_destroy(&bal_d);
    ut_moogladder_destroy(&filt_d);
    ut_tenv_destroy(&env_d);
     
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
