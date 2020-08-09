#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

int t_osc(ut_test *tst, ut_data *ut, const char *hash) {
    uint32_t n;
    int fail = 0;
    UTFLOAT osc;
    ut_osc *osc_d;
    ut_ftbl *ft_d; 

    ut_ftbl_create(ut, &ft_d, 2048);
    ut_osc_create(&osc_d);
    
    ut_gen_sine(ut, ft_d);
    ut_osc_init(ut, osc_d, ft_d, 0);
    osc_d->freq = 500;
    ut->len = 44100 * 5;
    
    for(n = 0; n < tst->size; n++) {
        osc = 0;
        ut_osc_compute(ut, osc_d, NULL, &osc);
        ut_out(ut, 0, osc);
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_ftbl_destroy(&ft_d);
    ut_osc_destroy(&osc_d);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}

