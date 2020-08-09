#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
   ut_ftbl *ft;
   ut_osc *osc;
   ut_clip *clp;
   ut_moogladder *filt;
} UserData;

int t_clip(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT out, osc, filt;
    
    UserData ud;
    ut_clip_create(&ud.clp);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 4096);
    ut_moogladder_create(&ud.filt);

    ut_gen_line(ut, ud.ft, "0 1 4096 -1");
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->freq = ut_midi2cps(48);
    ut_clip_init(ut, ud.clp);
    ut_moogladder_init(ut, ud.filt);
    ud.filt->freq = 1000; 
    ud.filt->res = 0.8;

    for(n = 0; n < tst->size; n++) {
        out = 0 , osc = 0 , filt = 0;
        ut_osc_compute(ut, ud.osc, NULL, &osc);
        ut_moogladder_compute(ut, ud.filt, &osc, &filt);
        ut_clip_compute(ut, ud.clp, &filt, &out);
        ut_test_add_sample(tst, out);
    }

    fail = ut_test_verify(tst, hash);

    ut_osc_destroy(&ud.osc);
    ut_clip_destroy(&ud.clp);
    ut_ftbl_destroy(&ud.ft);
    ut_moogladder_destroy(&ud.filt);
     
    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
