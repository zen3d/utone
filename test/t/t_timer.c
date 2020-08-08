#include "soundpipe.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    sp_timer *timer;
    sp_osc *osc;
    sp_ftbl *ft; 
    sp_tenv *tenv;
    sp_dmetro *dmetro;
} UserData;

int t_timer(sp_test *tst, sp_data *sp, const char *hash) 
{
    uint32_t n;
    int fail = 0;

    SPFLOAT osc = 0, timer = 0, clock = 0, tenv = 0;
    sp_srand(sp, 1234567);

    UserData ud;

    sp_timer_create(&ud.timer);
    sp_osc_create(&ud.osc);
    sp_ftbl_create(sp, &ud.ft, 2048);
    sp_tenv_create(&ud.tenv);
    sp_dmetro_create(&ud.dmetro);

    sp_timer_init(sp, ud.timer);
    sp_gen_sine(sp, ud.ft);
    sp_osc_init(sp, ud.osc, ud.ft, 0);
    sp_tenv_init(sp, ud.tenv);
    ud.tenv->atk = 0.1;
    ud.tenv->hold= 0.1;
    ud.tenv->rel = 0.1;
    sp_dmetro_init(sp, ud.dmetro);

    for(n = 0; n < tst->size; n++) {
        osc = 0; timer = 0; clock = 0; tenv = 0;

        if(sp->pos % 20000 == 0) {
            clock = 1;
        }
        sp_timer_compute(sp, ud.timer, &clock, &timer);
        ud.dmetro->time = timer;
        sp_dmetro_compute(sp, ud.dmetro, NULL, &timer);
        sp_tenv_compute(sp, ud.tenv, &timer, &tenv);
        sp_osc_compute(sp, ud.osc, NULL, &osc);
        sp->out[0] = osc * tenv;
        sp_test_add_sample(tst, sp->out[0]);
    }

    fail = sp_test_verify(tst, hash);

    sp_timer_destroy(&ud.timer);
    sp_ftbl_destroy(&ud.ft);
    sp_osc_destroy(&ud.osc);
    sp_tenv_destroy(&ud.tenv);
    sp_dmetro_destroy(&ud.dmetro);

    if(fail) return SP_NOT_OK;
    else return SP_OK;
}
