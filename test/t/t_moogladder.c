#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_noise *ns;
    ut_moogladder *moog;
    int counter;
} UserData;

int t_moogladder(ut_test *tst, ut_data *ut, const char *hash) 
{
    ut_srand(ut, 0); 
    uint32_t n;
    int fail = 0;

    UserData ud;
    ud.counter = 0;
    ut_noise_create(&ud.ns);
    ut_moogladder_create(&ud.moog);
    ut_noise_init(ut, ud.ns);
    ut_moogladder_init(ut, ud.moog);

    UTFLOAT in;

    for(n = 0; n < tst->size; n++) {
        in = 0;

        if(ud.counter == 0) {
            ud.moog->res = 0.8;
            ud.moog->freq = 500 + ut_rand(ut) % 4000;
        }

        ut_noise_compute(ut, ud.ns, NULL, &in);
        ut_moogladder_compute(ut, ud.moog, &in, &ut->out[0]); 
        ud.counter = (ud.counter + 1) % 5000;

        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);
 
    ut_noise_destroy(&ud.ns);
    ut_moogladder_destroy(&ud.moog);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
