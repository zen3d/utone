#include <stdlib.h>
#include <math.h>
#include "utone.h"

int ut_bitcrush_create(ut_bitcrush **p)
{
    *p = malloc(sizeof(ut_bitcrush));
    return UT_OK;
}

int ut_bitcrush_destroy(ut_bitcrush **p)
{
    ut_bitcrush *pp = *p;
    ut_fold_destroy(&pp->fold);
    free(*p);
    return UT_OK;
}

int ut_bitcrush_init(ut_data *ut, ut_bitcrush *p)
{
    p->bitdepth = 8;
    p->srate = 10000;
    ut_fold_create(&p->fold);
    ut_fold_init(ut, p->fold);
    return UT_OK;
}

int ut_bitcrush_compute(ut_data *ut, ut_bitcrush *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT bits = pow(2, floor(p->bitdepth));
    UTFLOAT foldamt = ut->sr / p->srate;
    UTFLOAT sig;
    *out = *in * 65536.0;
    *out += 32768;
    *out *= (bits / 65536.0);
    *out = floor(*out);
    *out = *out * (65536.0 / bits) - 32768;
    sig = *out;
    p->fold->incr = foldamt;
    ut_fold_compute(ut, p->fold, &sig, out);
    *out /= 65536.0;
    return UT_OK;
}
