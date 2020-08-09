#include <string.h>
#include <stdlib.h>
#include "utone.h"

int ut_reverse_create(ut_reverse **p)
{
    *p = malloc(sizeof(ut_reverse));
    return UT_OK;
}

int ut_reverse_destroy(ut_reverse **p)
{
    ut_reverse *pp = *p;
    ut_auxdata_free(&pp->buf);
    free(*p);
    return UT_OK;
}

int ut_reverse_init(ut_data *ut, ut_reverse *p, UTFLOAT delay)
{
    size_t size = delay * ut->sr * sizeof(UTFLOAT) * 2;
    p->bufpos = 0;
    ut_auxdata_alloc(&p->buf, size);
    p->bufsize = (uint32_t)p->buf.size / sizeof(UTFLOAT);
    return UT_OK;
}

int ut_reverse_compute(ut_data *ut, ut_reverse *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT *buf = (UTFLOAT *)p->buf.ptr;
    *out = buf[p->bufpos];
    buf[(p->bufsize - 1) - p->bufpos] = *in;
    p->bufpos = (p->bufpos + 1) % p->bufsize;
    return UT_OK;
}
