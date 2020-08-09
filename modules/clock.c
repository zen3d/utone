/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "utone.h"

int ut_clock_create(ut_clock **p)
{
    *p = malloc(sizeof(ut_clock));
    return UT_OK;
}

int ut_clock_destroy(ut_clock **p)
{
    free(*p);
    return UT_OK;
}

int ut_clock_init(ut_data *ut, ut_clock *p)
{
    p->subdiv = 1.0;
    p->bpm = 120;
    p->counter = 0;
    return UT_OK;
}

int ut_clock_compute(ut_data *ut, ut_clock *p, UTFLOAT *in, UTFLOAT *out)
{
    *out = 0.0;
    if(p->counter == 0 || *in != 0) {
        *out = 1.0;
        p->counter = (int)(ut->sr * (60.0 / (p->bpm * p->subdiv))) + 1;
    }
    p->counter--; 
    return UT_OK;
}
