#include <stdlib.h>
#include "utone.h"

int ut_scale_create(ut_scale **p)
{
    *p = malloc(sizeof(ut_scale));
    return UT_OK;
}

int ut_scale_destroy(ut_scale **p)
{
    free(*p);
    return UT_OK;
}

int ut_scale_init(ut_data *ut, ut_scale *p)
{
    p->min = -1;
    p->max = 1;
    return UT_OK;
}

int ut_scale_compute(ut_data *ut, ut_scale *p, UTFLOAT *in, UTFLOAT *out)
{
    *out =  *in * (p->max - p->min) + p->min;
    return UT_OK;
}
