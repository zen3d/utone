#include <stdlib.h>
#include "utone.h"

int ut_trand_create(ut_trand **p)
{
    *p = malloc(sizeof(ut_trand));
    return UT_OK;
}

int ut_trand_destroy(ut_trand **p)
{
    free(*p);
    return UT_OK;
}

int ut_trand_init(ut_data *ut, ut_trand *p)
{
    p->min = 0;
    p->max = 1;
    p->val = 0;
    return UT_OK;
}

int ut_trand_compute(ut_data *ut, ut_trand *p, UTFLOAT *in, UTFLOAT *out)
{
    if(*in != 0) {
        p->val = p->min + ((UTFLOAT) ut_rand(ut) / UT_RANDMAX) * (p->max - p->min);
        *out = p->val;
    } else {
        *out = p->val;
    }
    return UT_OK;
}
