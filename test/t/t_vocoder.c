#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_vocoder *vocoder;
    ut_blsaw *saw[3];
    ut_uta *diskin;
} UserData;

int t_vocoder(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT diskin = 0, vocoder = 0, saw = 0, tmp = 0;

    ut_srand(ut, 1234567);
    UserData ud;

    int i;

    int scale[] = {58, 65, 72};

    ut_vocoder_create(&ud.vocoder);
    ut_vocoder_init(ut, ud.vocoder);
   
    ut_uta_create(&ud.diskin); 
    ut_uta_init(ut, ud.diskin, SAMPDIR "oneart.uta");

    for(i = 0; i < 3; i++) {
        ut_blsaw_create(&ud.saw[i]);
        ut_blsaw_init(ut, ud.saw[i]);
        *ud.saw[i]->freq = ut_midi2cps(scale[i]);
    }

    for(n = 0; n < tst->size; n++) {
        diskin = 0; 
        vocoder = 0; 
        saw = 0; 
        tmp = 0;
        ut_uta_compute(ut, ud.diskin, NULL, &diskin);
        for(i = 0; i < 3; i++) {
            ut_blsaw_compute(ut, ud.saw[i], NULL, &tmp);
            saw += tmp;
        }
        saw *= 0.2;
        ut_vocoder_compute(ut, ud.vocoder, &diskin, &saw, &vocoder);
        ut_test_add_sample(tst, vocoder);
    }

    fail = ut_test_verify(tst, hash);

    ut_vocoder_destroy(&ud.vocoder);

    for(i = 0; i < 3; i++) {
        ut_blsaw_destroy(&ud.saw[i]);
    }

    ut_uta_destroy(&ud.diskin); 

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
