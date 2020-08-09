#include <stdlib.h>
#include "utone.h"

int ut_tdiv_create(ut_tdiv **p)
{
    *p = malloc(sizeof(ut_tdiv));
    return UT_OK;
}

int ut_tdiv_destroy(ut_tdiv **p)
{
    free(*p);
    return UT_OK;
}

int ut_tdiv_init(ut_data *ut, ut_tdiv *p)
{
    p->num = 2;
    p->counter = 0;
    p->offset = 0;
    return UT_OK;
}

int ut_tdiv_compute(ut_data *ut, ut_tdiv *p, UTFLOAT *in, UTFLOAT *out)
{
    *out = 0.0;
    if(*in != 0) {
        if(p->counter == p->offset) *out = 1.0;
        else *out = 0.0;
        p->counter = (p->counter + 1) % p->num;
    }
    return UT_OK;
}
