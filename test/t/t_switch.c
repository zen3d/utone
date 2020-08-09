#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_switch *sw;
    ut_osc *osc;
    ut_ftbl *ft;
    ut_metro *met;
    ut_osc *lfo;
    ut_fosc *fosc;
} UserData;

int t_switch(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT osc = 0, sw = 0, met = 0, fosc = 0, lfo = 0;

    ut_srand(ut, 1234567);
    UserData ud;

    ut_switch_create(&ud.sw);
    ut_osc_create(&ud.osc);
    ut_osc_create(&ud.lfo);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_metro_create(&ud.met);
    ut_fosc_create(&ud.fosc);

    ut_switch_init(ut, ud.sw);
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ut_osc_init(ut, ud.lfo, ud.ft, 0);
    ud.lfo->amp = 100;
    ud.lfo->freq = 6;
    ut_fosc_init(ut, ud.fosc, ud.ft);
    ut_metro_init(ut, ud.met);
    ud.met->freq = 2.5;

    for(n = 0; n < tst->size; n++) {
        osc = 0; sw = 0; met = 0; fosc = 0; lfo = 0;
        ut_osc_compute(ut, ud.lfo, NULL, &lfo);
        ud.osc->freq = 550 + lfo;
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut_fosc_compute(ut, ud.fosc, NULL, &fosc);
        ut_metro_compute(ut, ud.met, NULL, &met);
        ut_switch_compute(ut, ud.sw, &met, &osc, &fosc, &sw);
        ut_test_add_sample(tst, sw);
    }

    fail = ut_test_verify(tst, hash);

    ut_switch_destroy(&ud.sw);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_osc_destroy(&ud.lfo);
    ut_fosc_destroy(&ud.fosc);
    ut_metro_destroy(&ud.met);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
