#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_fog *fog;
    ut_ftbl *wav;
    ut_ftbl *win;
    ut_phasor *phs;
} UserData;

int t_fog(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT phs = 0, fog = 0;

    ut_srand(ut, 1234567);
    UserData ud;

    ut_ftbl_loadfile(ut, &ud.wav, SAMPDIR "oneart.wav");
    ut_ftbl_create(ut, &ud.win, 1024);
    ut_fog_create(&ud.fog);
    ut_phasor_create(&ud.phs);

    ut_gen_composite(ut, ud.win, "0.5 0.5 270 0.5");

    ut_fog_init(ut, ud.fog, ud.wav, ud.win, 100, 0);
    ud.fog->trans = 0.9;

    ut_phasor_init(ut, ud.phs, 0);
    ud.phs->freq = 0.3 / ((UTFLOAT)ud.wav->size / ut->sr); 

    for(n = 0; n < tst->size; n++) {
        phs = 0; 
        fog = 0;
        ut_phasor_compute(ut, ud.phs, NULL, &phs);
        ud.fog->spd = phs;
        ut_fog_compute(ut, ud.fog, NULL, &fog);
        ut_test_add_sample(tst, fog);
    }

    fail = ut_test_verify(tst, hash);

    ut_fog_destroy(&ud.fog);
    ut_ftbl_destroy(&ud.wav);
    ut_ftbl_destroy(&ud.win);
    ut_phasor_destroy(&ud.phs);


    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
