#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_diskin *disk;
    ut_zitarev *rev;
    int counter;
} UserData;

int t_zitarev(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;

    UTFLOAT in = 0;
    UTFLOAT out = 0;
    UTFLOAT foo = 0;

    ut_srand(ut,12345);
    UserData ud;
    ud.counter = 0;
    ut_diskin_create(&ud.disk);
    ut_zitarev_create(&ud.rev);

    ut_diskin_init(ut, ud.disk, SAMPDIR "oneart.wav");
    ut_zitarev_init(ut, ud.rev);
    *ud.rev->level = 0;
    *ud.rev->in_delay = 20;

    for(n = 0; n < tst->size; n++) {
        in = 0;
        out = 0;
        foo = 0;

        ut_diskin_compute(ut, ud.disk, NULL, &in);
        ut_zitarev_compute(ut, ud.rev, &in, &in, &out, &foo);
        ut_test_add_sample(tst, out);
    }

    fail = ut_test_verify(tst, hash);

    ut_diskin_destroy(&ud.disk);
    ut_zitarev_destroy(&ud.rev);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
