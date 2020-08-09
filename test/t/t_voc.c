
#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_voc *voc;
    ut_osc *osc;
    ut_ftbl *ft;
} UserData;

int t_voc(ut_test *tst, ut_data *ut, const char *hash)
{
    uint32_t n;
    UserData ud;

    int fail = 0;
    UTFLOAT osc, voc;
    ut_voc_create(&ud.voc);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_voc_init(ut, ud.voc);
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->amp = 1;
    ud.osc->freq = 0.1;

    for(n = 0; n < tst->size; n++) {
        /* compute samples and add to test buffer */
        osc = 0;
        voc = 0;
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        if(ut_voc_get_counter(ud.voc) == 0) {
            osc = 12 + 16 * (0.5 * (osc + 1));
            ut_voc_set_tongue_shape(ud.voc, osc, 2.9);
        }
        ut_voc_compute(ut, ud.voc, &voc);
        ut_test_add_sample(tst, voc);
    }

    fail = ut_test_verify(tst, hash);

    ut_voc_destroy(&ud.voc);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}

