#include <stdlib.h>
#include "utone.h"

int ut_slice_create(ut_slice **p)
{
    *p = malloc(sizeof(ut_slice));
    return UT_OK;
}

int ut_slice_destroy(ut_slice **p)
{
    free(*p);
    return UT_OK;
}

int ut_slice_init(ut_data *ut, ut_slice *p, ut_ftbl *vals, ut_ftbl *buf)
{
    p->vals = vals;
    p->buf = buf;
    p->pos = 0;
    p->nextpos = 0;
    p->id = 0;
    return UT_OK;
}

int ut_slice_compute(ut_data *ut, ut_slice *p, UTFLOAT *in, UTFLOAT *out)
{
    *out = 0;
    if(*in != 0) {
        if(p->id < p->vals->size) {
            p->pos = p->vals->tbl[p->id];
            if(p->id == p->vals->size - 1) {
                p->nextpos = p->buf->size;
            } else {
                p->nextpos = p->vals->tbl[p->id + 1];
            }
        }
    }

    if(p->pos < p->nextpos) {
        *out = p->buf->tbl[p->pos];
        p->pos++;
    }

    return UT_OK;
}
