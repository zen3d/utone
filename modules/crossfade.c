#include <stdlib.h>
#include "utone.h"

int ut_crossfade_create(ut_crossfade **p)
{
    *p = malloc(sizeof(ut_crossfade));
    return UT_OK;
}

int ut_crossfade_destroy(ut_crossfade **p)
{
    free(*p);
    return UT_OK;
}

int ut_crossfade_init(ut_data *ut, ut_crossfade *p)
{
    p->pos = 0.5;
    return UT_OK;
}

int ut_crossfade_compute(ut_data *ut, ut_crossfade *p, UTFLOAT *in1, UTFLOAT *in2, UTFLOAT *out)
{
    *out = *in2 * p->pos + *in1 * (1 - p->pos);
    return UT_OK;
}
