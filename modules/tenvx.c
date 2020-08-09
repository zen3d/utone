#include <stdlib.h>
#include <math.h>
#include "utone.h"

int ut_tenvx_create(ut_tenvx **p)
{
    *p = malloc(sizeof(ut_tenvx));
    return UT_OK;
}

int ut_tenvx_destroy(ut_tenvx **p)
{
    free(*p);
    return UT_OK;
}


int ut_tenvx_init(ut_data *ut, ut_tenvx *p)
{
    p->hold = 0.5;
    p->atk = 0.5;
    p->rel = 0.5;
    p->a_a = p->b_a = 0;
    p->a_r = p->b_r = 0;
    p->y = 0;
    p->count = (uint32_t) (p->hold * ut->sr);
    return UT_OK;
}


int ut_tenvx_compute(ut_data *ut, ut_tenvx *p, UTFLOAT *in, UTFLOAT *out)
{
    *out = 0;

    if(*in != 0) {
        p->a_a = exp(-1.0/(p->atk * ut->sr));
        p->b_a = 1.0 - p->a_a;
        p->a_r = exp(-1.0/(p->rel * ut->sr));
        p->b_r = 1.0 - p->a_r;
        p->count = (uint32_t) (p->hold * ut->sr);
    }

    if(p->count > 0) {
        *out = p->b_a + p->a_a * p->y;
        p->y = *out;
        p->count--;
    } else {
        *out = p->a_r * p->y;
        p->y = *out;
    }

    return UT_OK;
}
