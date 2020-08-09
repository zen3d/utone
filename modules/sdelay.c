#include <stdlib.h>
#include "utone.h"

int ut_sdelay_create(ut_sdelay **p)
{
    *p = malloc(sizeof(ut_sdelay));
    ut_sdelay *pp = *p;
    pp->size = 0;
    return UT_OK;
}

int ut_sdelay_destroy(ut_sdelay **p)
{
    ut_sdelay *pp = *p;

    if(pp->size > 0) {
        free(pp->buf);
    }

    free(*p);
    return UT_OK;
}

int ut_sdelay_init(ut_data *ut, ut_sdelay *p, int size)
{
    int n;
    p->size = size;
    p->buf = malloc(size * sizeof(UTFLOAT));
    for(n = 0; n < p->size; n++) p->buf[n] = 0;
    p->pos = 0;
    return UT_OK;
}

int ut_sdelay_compute(ut_data *ut, ut_sdelay *p, UTFLOAT *in, UTFLOAT *out)
{
    *out = p->buf[p->pos];
    p->buf[p->pos] = *in;
    p->pos = (p->pos + 1) % p->size;
    return UT_OK;
}
