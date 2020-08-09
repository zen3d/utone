#include <stdlib.h>
#include "utone.h"

int ut_samphold_create(ut_samphold **p)
{
    *p = malloc(sizeof(ut_samphold));
    return UT_OK;
}

int ut_samphold_destroy(ut_samphold **p)
{
    free(*p);
    return UT_OK;
}

int ut_samphold_init(ut_data *ut, ut_samphold *p)
{
    p->val = 0;
    return UT_OK;
}

int ut_samphold_compute(ut_data *ut, ut_samphold *p, UTFLOAT *trig, UTFLOAT *in, UTFLOAT *out)
{
    if(*trig != 0) {
        p->val = *in;
    }
    *out = p->val;
    return UT_OK;
}
