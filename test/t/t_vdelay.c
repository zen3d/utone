#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_osc *osc, *lfo;
    ut_ftbl *ft, *sine;
    ut_vdelay *del;
} UserData;

int t_vdelay(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UserData ud;
    UTFLOAT freq = 0.0, del = 0.0, osc = 0.0;

    ut_vdelay_create(&ud.del);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.sine, 4096);
    ut_osc_create(&ud.lfo);

    ut_vdelay_init(ut, ud.del, 0.5);
    ut_gen_file(ut, ud.ft, "Formant04.wav");
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->freq = ut_midi2cps(50);

    ut_gen_sine(ut, ud.sine);
    ut_osc_init(ut, ud.lfo, ud.sine, 0);
    ud.lfo->freq = 0.2;

    for(n = 0; n < tst->size; n++) {
        freq = 0.0, del = 0.0, osc = 0.0;
        ut_osc_compute(ut, ud.lfo, NULL, &freq);
        freq = 1.0 + (freq * 0.5);
        freq = 0.02 + (freq * 0.02);
        ud.del->del = freq;
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut_vdelay_compute(ut, ud.del, &osc, &del);
        ut->out[0] = del * 0.5 + osc * 0.5;
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);
    
    ut_vdelay_destroy(&ud.del);
    ut_ftbl_destroy(&ud.ft);
    ut_ftbl_destroy(&ud.sine);
    ut_osc_destroy(&ud.osc);
    ut_osc_destroy(&ud.lfo);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
