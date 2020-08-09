#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

int t_blsquare(ut_test *tst, ut_data *ut, const char *hash) {
    uint32_t n;
    int fail = 0;
    UTFLOAT blsquare;
    ut_blsquare *blsquare_d;

    ut_blsquare_create(&blsquare_d);

    ut_blsquare_init(ut, blsquare_d);
    *blsquare_d->freq = 500;
    *blsquare_d->width = 0.4;
    ut->len = 44100 * 5;

    for(n = 0; n < tst->size; n++) {
        blsquare = 0;
        ut_blsquare_compute(ut, blsquare_d, NULL, &blsquare);
        ut_out(ut, 0, blsquare);
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_blsquare_destroy(&blsquare_d);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}

