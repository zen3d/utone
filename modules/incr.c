#include <stdlib.h>
#include "utone.h"

#ifndef max
#define max(a, b) ((a > b) ? a : b)
#endif

#ifndef min
#define min(a, b) ((a < b) ? a : b)
#endif


int ut_incr_create(ut_incr **p)
{
    *p = malloc(sizeof(ut_incr));
    return UT_OK;
}

int ut_incr_destroy(ut_incr **p)
{
    free(*p);
    return UT_OK;
}

int ut_incr_init(ut_data *ut, ut_incr *p, UTFLOAT val)
{
    p->min = 0;
    p->max = 1;
    p->step = 0.1;
    p->val = val;
    return UT_OK;
}

int ut_incr_compute(ut_data *ut, ut_incr *p, UTFLOAT *in, UTFLOAT *out)
{
    if(*in > 0 ) {
        p->val += p->step;
        p->val = max(min(p->val, p->max), p->min);
    } else if (*in < 0) {
        p->val -= p->step;
        p->val = max(min(p->val, p->max), p->min);
    }
    *out = p->val;
    return UT_OK;
}
