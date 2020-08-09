#include <stdlib.h>
#include "utone.h"

int ut_maygate_create(ut_maygate **p)
{
    *p = malloc(sizeof(ut_maygate));
    return UT_OK;
}

int ut_maygate_destroy(ut_maygate **p)
{
    free(*p);
    return UT_OK;
}

int ut_maygate_init(ut_data *ut, ut_maygate *p)
{
    p->prob = 0.0;
    p->gate = 0;
    p->mode = 0;
    return UT_OK;
}

int ut_maygate_compute(ut_data *ut, ut_maygate *p, UTFLOAT *in, UTFLOAT *out)
{
    if(*in == 0) {
        if(p->mode) {
            *out = 0;
        } else {
            *out = p->gate;
        }
        return UT_OK;
    }

    if((1.0 * ut_rand(ut) / UT_RANDMAX) <= p->prob) {
        *out = 1;
        p->gate = 1;
    } else {
        *out = 0;
        p->gate = 0;
    }
    return UT_OK;
}
