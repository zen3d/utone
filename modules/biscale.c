#include <stdlib.h>
#include "utone.h"

int ut_biscale_create(ut_biscale **p)
{
    *p = malloc(sizeof(ut_biscale));
    return UT_OK;
}

int ut_biscale_destroy(ut_biscale **p)
{
    free(*p);
    return UT_OK;
}

int ut_biscale_init(ut_data *ut, ut_biscale *p)
{
    p->min = 0;
    p->max = 1;
    return UT_OK;
}

int ut_biscale_compute(ut_data *ut, ut_biscale *p, UTFLOAT *in, UTFLOAT *out)
{
    *out = p->min + (*in + 1.0) / 2.0 * (p->max - p->min);
    return UT_OK;
}
