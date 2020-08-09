#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

int t_bltriangle(ut_test *tst, ut_data *ut, const char *hash) {
    uint32_t n;
    int fail = 0;
    UTFLOAT bltriangle;
    ut_bltriangle *bltriangle_d;

    ut_bltriangle_create(&bltriangle_d);

    ut_bltriangle_init(ut, bltriangle_d);
    *bltriangle_d->freq = 500;
    ut->len = 44100 * 5;

    for(n = 0; n < tst->size; n++) {
        bltriangle = 0;
        ut_bltriangle_compute(ut, bltriangle_d, NULL, &bltriangle);
        ut_out(ut, 0, bltriangle);
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_bltriangle_destroy(&bltriangle_d);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}

