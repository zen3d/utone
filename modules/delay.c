#include <stdlib.h>
#include <math.h>
#include "utone.h"

int ut_delay_create(ut_delay **p)
{
    *p = malloc(sizeof(ut_delay));
    return UT_OK;
}

int ut_delay_destroy(ut_delay **p)
{
    ut_delay *pp = *p;
    ut_auxdata_free(&pp->buf);
    free(*p);
    return UT_OK;
}

int ut_delay_init(ut_data *ut, ut_delay *p, UTFLOAT time)
{
    p->time = time;
    p->bufsize = round(time * ut->sr);
    ut_auxdata_alloc(&p->buf, p->bufsize * sizeof(UTFLOAT));
    p->bufpos = 0;
    p->feedback = 0;
    p->last = 0;
    return UT_OK;
}

int ut_delay_compute(ut_data *ut, ut_delay *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT delay = 0, sig = 0;
    UTFLOAT *buf = (UTFLOAT *)p->buf.ptr; 
    delay = buf[p->bufpos];
    sig = (delay * p->feedback) + *in;
    buf[p->bufpos] = sig;
    p->bufpos = (p->bufpos + 1) % p->bufsize;
    *out = delay;
    return UT_OK;
}
