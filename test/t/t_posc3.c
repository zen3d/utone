#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_posc3 *posc3;
    ut_ftbl *ft; 
    int counter;
} UserData;

int t_posc3(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    
    ut_srand(ut, 123456);
    UserData ud;
    ud.counter = 0;
    ut_ftbl_create(ut, &ud.ft, 1024);
    ut_posc3_create(&ud.posc3);
    
    ut_gen_sine(ut, ud.ft);
    ut_posc3_init(ut, ud.posc3, ud.ft);
    ud.posc3->freq = 500;

    for(n = 0; n < tst->size; n++) {
        if(ud.counter == 0){
            ud.posc3->freq = 500 + ut_rand(ut) % 2000;
        }
        ut_posc3_compute(ut, ud.posc3, NULL, &ut->out[0]);
        ud.counter = (ud.counter + 1) % 4410;
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_ftbl_destroy(&ud.ft);
    ut_posc3_destroy(&ud.posc3);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
