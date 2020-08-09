#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_uta *uta;
} UserData;

int t_uta(ut_test *tst, ut_data *ut, const char *hash) 
{
    UserData ud;
    uint32_t n;
    UTFLOAT uta;
    int fail = 0;

    ut_srand(ut, 1234567);
    ut_uta_create(&ud.uta);
    ut_uta_init(ut, ud.uta, SAMPDIR "oneart.uta");


    for(n = 0; n < tst->size; n++) {
        uta = 0;
        ut_uta_compute(ut, ud.uta, NULL, &uta);
        ut_test_add_sample(tst, uta);
    }

    fail = ut_test_verify(tst, hash);

    ut_uta_destroy(&ud.uta);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
