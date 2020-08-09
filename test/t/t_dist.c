#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_fosc *osc;
    ut_ftbl *ft;
    ut_dist *ds;
    ut_osc *lfo;
} UserData;

int t_dist(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT osc = 0, lfo = 0, out = 0;
    UserData ud;
    
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_fosc_create(&ud.osc);
    ut_dist_create(&ud.ds);
    ut_osc_create(&ud.lfo);

    ut_gen_sine(ut, ud.ft);
    ut_fosc_init(ut, ud.osc, ud.ft);
    ud.osc->freq = 60;
    ut_dist_init(ut, ud.ds);
    ud.ds->pregain = 10;
    ut_osc_init(ut, ud.lfo, ud.ft, 0);
    ud.lfo->freq = 0.5;


    for(n = 0; n < tst->size; n++) {
        osc = 0, lfo = 0, out = 0;
        ut_osc_compute(ut, ud.lfo, NULL, &lfo);
        lfo = 7 * (0.5 * (lfo + 1));
        ud.osc->indx = lfo;
        ut_fosc_compute(ut, ud.osc, NULL, &osc);
        ut_dist_compute(ut, ud.ds, &osc, &out);

        ut_test_add_sample(tst, out);
    }

    fail = ut_test_verify(tst, hash);
     
    ut_ftbl_destroy(&ud.ft);
    ut_fosc_destroy(&ud.osc);
    ut_dist_destroy(&ud.ds);
    ut_osc_destroy(&ud.lfo);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
