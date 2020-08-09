#include <math.h>
#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_noise *ns;
    ut_eqfil *eqfil;
    int counter;
} UserData;

int t_eqfil(ut_test *tst, ut_data *ut, const char *hash) 
{
    ut_srand(ut, 0); 
    uint32_t n;
    int fail = 0;
    UserData ud;
    UTFLOAT in = 0;
    UTFLOAT out = 0;
    
    ud.counter = 0;
    ut_noise_create(&ud.ns);
    ut_eqfil_create(&ud.eqfil);
    ut_noise_init(ut, ud.ns);
    ut_eqfil_init(ut, ud.eqfil);

    for(n = 0; n < tst->size; n++) {
        in = 0;
        out = 0;
        if(ud.counter == 0) {
            ud.eqfil->freq = 500 + ut_rand(ut) % 4000;
            ud.eqfil->bw = fabs(ud.eqfil->freq * 0.5);
        }
        ut_noise_compute(ut, ud.ns, NULL, &in);
        ut_eqfil_compute(ut, ud.eqfil, &in, &out); 
        ud.counter = (ud.counter + 1) % 5000;
        ut_test_add_sample(tst, out);
    }

    fail = ut_test_verify(tst, hash);
     
    ut_noise_destroy(&ud.ns);
    ut_eqfil_destroy(&ud.eqfil);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
