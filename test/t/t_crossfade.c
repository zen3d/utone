#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_crossfade *crossfade;
    ut_osc *osc;
    ut_ftbl *ft; 
    ut_osc *lfo;
    ut_noise *ns;
} UserData;

int t_crossfade(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT osc = 0, crossfade = 0, ns = 0, lfo = 0;

    UserData ud;
    ut_srand(ut, 12345);
    ut_crossfade_create(&ud.crossfade);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_osc_create(&ud.lfo);
    ut_noise_create(&ud.ns);

    ut_crossfade_init(ut, ud.crossfade);
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ut_osc_init(ut, ud.lfo, ud.ft, 0);
    ud.lfo->amp = 1;
    ud.lfo->freq = 1;
    ut_noise_init(ut, ud.ns);
    ud.ns->amp = 0.1;

    
    for(n = 0; n < tst->size; n++) {
        osc = 0, crossfade = 0, ns = 0, lfo = 0;
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut_osc_compute(ut, ud.lfo, NULL, &lfo);
        ut_noise_compute(ut, ud.ns, NULL, &ns);
        ud.crossfade->pos = (lfo + 1) * 0.5;
        ut_crossfade_compute(ut, ud.crossfade, &osc, &ns, &crossfade);
        ut_test_add_sample(tst, crossfade);
    }

    fail = ut_test_verify(tst, hash);

    ut_crossfade_destroy(&ud.crossfade);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_osc_destroy(&ud.lfo);
    ut_noise_destroy(&ud.ns);

    if(fail) return UT_NOT_OK;
    /* fail by default */
    else return UT_OK;
}
