#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

int t_blsaw(ut_test *tst, ut_data *ut, const char *hash) {
    uint32_t n;
    int fail = 0;
    UTFLOAT blsaw;
    ut_blsaw *blsaw_d;

    ut_blsaw_create(&blsaw_d);

    ut_blsaw_init(ut, blsaw_d);
    *blsaw_d->freq = 500;
    ut->len = 44100 * 5;

    for(n = 0; n < tst->size; n++) {
        blsaw = 0;
        ut_blsaw_compute(ut, blsaw_d, NULL, &blsaw);
        ut_out(ut, 0, blsaw);
        ut_test_add_sample(tst, ut->out[0]);
    }

    fail = ut_test_verify(tst, hash);

    ut_blsaw_destroy(&blsaw_d);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}

