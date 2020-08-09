#include <stdlib.h>
#include "utone.h"

int ut_tgate_create(ut_tgate **p)
{
    *p = malloc(sizeof(ut_tgate));
    return UT_OK;
}

int ut_tgate_destroy(ut_tgate **p)
{
    free(*p);
    return UT_OK;
}

int ut_tgate_init(ut_data *ut, ut_tgate *p)
{
    p->time = 0;
    p->timer = 0;
    return UT_OK;
}

int ut_tgate_compute(ut_data *ut, ut_tgate *p, UTFLOAT *in, UTFLOAT *out)
{
    *out = 0;
    if(*in != 0) {
        p->timer = p->time * ut->sr;
    }
    if(p->timer != 0) {
        *out = 1;
        p->timer--;
    }
    return UT_OK;
}
