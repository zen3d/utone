#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_autowah *autowah;
    ut_uta *disk;
} UserData;

int t_autowah(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT disk = 0, autowah = 0;

    UserData ud;

    ut_autowah_create(&ud.autowah);
    ut_uta_create(&ud.disk);

    ut_uta_init(ut, ud.disk, SAMPDIR "oneart.uta");
    ut_autowah_init(ut, ud.autowah);
    *ud.autowah->wah = 1.0;
    
    for(n = 0; n < tst->size; n++) {
        disk = 0; 
        autowah = 0;
        ut_uta_compute(ut, ud.disk, NULL, &disk);
        ut_autowah_compute(ut, ud.autowah, &disk, &autowah);
        ut_test_add_sample(tst, autowah);
    }

    fail = ut_test_verify(tst, hash);

    ut_autowah_destroy(&ud.autowah);
    ut_uta_destroy(&ud.disk);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
