#include <stdlib.h>
#include "utone.h"

int ut_timer_create(ut_timer **p)
{
    *p = malloc(sizeof(ut_timer));
    return UT_OK;
}

int ut_timer_destroy(ut_timer **p)
{
    free(*p);
    return UT_OK;
}

int ut_timer_init(ut_data *ut, ut_timer *p)
{
    p->mode = 0;
    p->pos = 0;
    p->time = 0;
    return UT_OK;
}

int ut_timer_compute(ut_data *ut, ut_timer *p, UTFLOAT *in, UTFLOAT *out)
{
    if(*in != 0) {
        if(p->mode == 0) {
            p->pos = 0;
            p->mode = 1;
        } else if(p->mode == 1) {
            p->time = (UTFLOAT) p->pos / ut->sr;
            p->mode = 0;
        }
    }

    if(p->mode == 1) {
        p->pos++;
    }

    *out = p->time;
    return UT_OK;
}
