#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_expon *line;
    ut_osc *osc;
    ut_ftbl *ft;
} UserData;

int t_expon(ut_test *tst, ut_data *ut, const char *hash) 
{

    ut_srand(ut, 1234567);
    uint32_t n;
    int fail = 0;
    UTFLOAT osc = 0, line = 0;
    UTFLOAT tick = 0;
    UserData ud;

    ut_expon_create(&ud.line);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_expon_init(ut, ud.line);
    ud.line->a = 100;
    ud.line->dur = 3;
    ud.line->b = 400;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);

    ut->len = 44100 * 5;

    for(n = 0; n < tst->size; n++) {
        if(n == 0) tick = 1; else tick = 0;
        ut_expon_compute(ut, ud.line, &tick, &line);
        ud.osc->freq = line;
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut->out[0] = osc;

        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_expon_destroy(&ud.line);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
 
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
