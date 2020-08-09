#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_oscmorph *oscmorph;
    ut_ftbl *wt1;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

int t_oscmorph(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT osc = 0, oscmorph = 0;

    ut_srand(ut, 1234567);
    UserData ud;

    ut_oscmorph_create(&ud.oscmorph);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_ftbl_create(ut, &ud.wt1, 2048);

    ut_gen_line(ut, ud.wt1, "0 1 2048 -1");
    ut_gen_sine(ut, ud.ft);

    ut_ftbl *ft_array[] = {ud.wt1, ud.ft};
    ut_oscmorph_init(ut, ud.oscmorph, ft_array, 2, 0);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->freq = 1;
    ud.osc->amp = 1;


    for(n = 0; n < tst->size; n++) {
        osc = 0, oscmorph = 0;
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        osc = (1 + osc) * 0.5;
        ud.oscmorph->wtpos = osc;
        ut_oscmorph_compute(ut, ud.oscmorph, NULL, &oscmorph);
        ut_test_add_sample(tst, oscmorph);
    }

    fail = ut_test_verify(tst, hash);

    ut_oscmorph_destroy(&ud.oscmorph);
    ut_ftbl_destroy(&ud.ft);
    ut_ftbl_destroy(&ud.wt1);
    ut_osc_destroy(&ud.osc);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
