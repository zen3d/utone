#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_tabread *tr;
    ut_ftbl *ft;
    ut_phasor *phasor;
} UserData;

int t_tabread(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT tab = 0.0, phasor = 0.0;

    ut_srand(ut, 123456);
    UserData ud;

    ut_tabread_create(&ud.tr);

    ut_phasor_create(&ud.phasor);

    ut_ftbl_create(ut, &ud.ft, 395393);
    ut_gen_file(ut, ud.ft, "oneart.wav");

    ut_tabread_init(ut, ud.tr, ud.ft, 1);

    /* since mode = 1, offset 5% into file */
    ud.tr->offset = 0.05;
    /* no wraparound */
    ud.tr->wrap = 0;

    ut_phasor_init(ut, ud.phasor, 0);
    /* set playback rate to half.uteed, or 1/(t * 2) */
    ud.phasor->freq = 1 / (8.97 * 2);
    ut->len = 44100 * 5;


    for(n = 0; n < tst->size; n++) {
        tab = 0.0; phasor = 0.0;
        ut_phasor_compute(ut, ud.phasor, NULL, &phasor);
        ud.tr->index = phasor;
        ut_tabread_compute(ut, ud.tr, NULL, &tab);
        ut_test_add_sample(tst, 0);
    }

    fail = ut_test_verify(tst, hash);

    ut_phasor_destroy(&ud.phasor);
    ut_tabread_destroy(&ud.tr);
    ut_ftbl_destroy(&ud.ft);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
