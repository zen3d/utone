#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct user_data {
    ut_ftbl *ft, *amps;
    ut_osc *osc;
    UTFLOAT fc;
} UserData;

int t_padsynth(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT out = 0;

    UserData ud;
    int i;
    ut_srand(ut, 12345);
    ut_ftbl_create(ut, &ud.amps, 64);
    ut_ftbl_create(ut, &ud.ft, 262144);
    ut_osc_create(&ud.osc);

    ud.amps->tbl[0] = 0.0;

    for(i = 1; i < ud.amps->size; i++){
        ud.amps->tbl[i] = 1.0 / i;
        if((i % 2) == 0) ud.amps->tbl[i] *= 2.0; 
    }

    
    /* Discovered empirically. multiply frequency by this constant. */
    ud.fc = 1 / (6.0 * 440); 
    ut_gen_padsynth(ut, ud.ft, ud.amps, ut_midi2cps(60), 40.0);

    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->freq = ut_midi2cps(70) * ud.fc;
    ud.osc->amp = 1.0;

    for(n = 0; n < tst->size; n++) {
        ut_osc_compute(ut, ud.osc, NULL, &out);
        ut_test_add_sample(tst, out);
    }

    fail = ut_test_verify(tst, hash);

    ut_osc_destroy(&ud.osc);
    ut_ftbl_destroy(&ud.amps);
    ut_ftbl_destroy(&ud.ft);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
