#include <stdlib.h>
#include "utone.h"

int ut_line_create(ut_line **p)
{
    *p = malloc(sizeof(ut_line));
    return UT_OK;
}

int ut_line_destroy(ut_line **p)
{
    free(*p);
    return UT_OK;
}

static void line_reinit(ut_data *ut, ut_line *p)
{
    UTFLOAT onedsr = 1.0 / ut->sr;
    p->incr = (UTFLOAT)((p->b - p->a) / (p->dur)) * onedsr;
    p->val = p->a;
    p->stime = 0;
    p->sdur = ut->sr * p->dur;
}

int ut_line_init(ut_data *ut, ut_line *p)
{
    p->a = 0;
    p->dur = 0.5;
    p->b = 1;
    line_reinit(ut, p);
    p->init = 1;
    return UT_OK;
}

int ut_line_compute(ut_data *ut, ut_line *p, UTFLOAT *in, UTFLOAT *out)
{
    if(*in != 0 ) {
        line_reinit(ut, p);
        p->init = 0;
    }

    if(p->init) {
        *out = 0;
        return UT_OK;
    }

    if(p->stime < p->sdur) {
        UTFLOAT val = p->val;
        p->val += p->incr;
        p->stime++;
        *out = val;
    } else {
        *out = p->b;
    }

    return UT_OK;
}
