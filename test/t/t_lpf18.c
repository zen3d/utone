#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_osc *osc[3];
    ut_ftbl *ft;
    ut_lpf18 *lpf;
    ut_osc *lfo;
    ut_ftbl *sine_ft;
} UserData;

int t_lpf18(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;

    ut_srand(ut, 0); 
    int i;
    UserData ud;
    ut_ftbl_create(ut, &ud.ft, 4096);
    for(i = 0; i < 3; i++) ut_osc_create(&ud.osc[i]);
    ut_lpf18_create(&ud.lpf);
    ut_osc_create(&ud.lfo);
    ut_ftbl_create(ut, &ud.sine_ft, 4096);
    ut_gen_sine(ut, ud.sine_ft);

    ut_gen_line(ut, ud.ft, "0 1 4096 -1");
    ut_osc_init(ut, ud.osc[0], ud.ft, 0);
    ud.osc[0]->freq = ut_midi2cps(40 - 0.05);
    ut_osc_init(ut, ud.osc[1], ud.ft, 0);
    ud.osc[1]->freq = ut_midi2cps(40 - 12);
    ut_osc_init(ut, ud.osc[2], ud.ft, 0);
    ud.osc[2]->freq = ut_midi2cps(40 + 0.05);
    ut_lpf18_init(ut, ud.lpf);
    ut_osc_init(ut, ud.lfo, ud.sine_ft, 0);
    ud.lfo->freq = 0.4;
    UTFLOAT out = 0, osc = 0, filt = 0, lfo = 0;

    for(n = 0; n < tst->size; n++) {
        int i;
        for(i = 0; i < 3; i++) {
            ut_osc_compute(ut, ud.osc[i], NULL, &osc);
            out += osc * 0.3;
        }
        ut_osc_compute(ut, ud.lfo, NULL, &lfo);
        ud.lpf->cutoff = 100 + 3000 * (0.5 * (lfo + 1));
        ut_lpf18_compute(ut, ud.lpf, &out, &filt);
        out = filt;
        ut_test_add_sample(tst, out);
    }
    
    fail = ut_test_verify(tst, hash);

    ut_ftbl_destroy(&ud.ft);
    for(i = 0; i < 3; i++) ut_osc_destroy(&ud.osc[i]);
    ut_lpf18_destroy(&ud.lpf);
    ut_osc_destroy(&ud.lfo);
    ut_ftbl_destroy(&ud.sine_ft);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
