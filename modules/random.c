#include <stdlib.h>
#include "utone.h"

int ut_random_create(ut_random **p)
{
    *p = malloc(sizeof(ut_random));
    return UT_OK;
}

int ut_random_destroy(ut_random **p)
{
    free(*p);
    return UT_OK;
}

int ut_random_init(ut_data *ut, ut_random *p)
{
    p->min = -1;
    p->max = 1;
    return UT_OK;
}

int ut_random_compute(ut_data *ut, ut_random *p, UTFLOAT *in, UTFLOAT *out)
{
    /* Send the signal's input to the output */
    UTFLOAT rnd = ((ut_rand(ut) % RAND_MAX) / (RAND_MAX * 1.0));
    rnd *= (p->max - p->min);
    rnd += p->min;
    *out = rnd;
    return UT_OK;
}
