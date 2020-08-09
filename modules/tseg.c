#include <stdlib.h>
#include <math.h>
#include "utone.h"

int ut_tseg_create(ut_tseg **p)
{
    *p = malloc(sizeof(ut_tseg));
    return UT_OK;
}

int ut_tseg_destroy(ut_tseg **p)
{
    free(*p);
    return UT_OK;
}

int ut_tseg_init(ut_data *ut, ut_tseg *p, UTFLOAT ibeg)
{
    p->beg = ibeg;
    p->end = 1.0;
    p->val = ibeg;
    p->type = -3;
    p->slope = 1.0;
    p->dur = 1.0;
    p->tdivnsteps = 0.0;
    p->count = 0;
    p->steps = p->dur * ut->sr;
    return UT_OK;
}

int ut_tseg_compute(ut_data *ut, ut_tseg *p, UTFLOAT *in, UTFLOAT *out)
{
    *out = p->val;
    if(*in != 0) {
        p->slope = 1.0 / (1.0 - exp(p->type));
        p->beg = p->val;
        p->count = 0;
        p->steps = p->dur * ut->sr;
        p->tdivnsteps = (UTFLOAT)p->type / (p->steps - 1);
    }
    if(p->count < p->steps) {
        *out = p->beg + (p->end - p->beg) * 
            ((1 - exp(p->count * p->tdivnsteps)) * p->slope);
        p->val = *out;
        p->count++;
    }
    return UT_OK;
}
