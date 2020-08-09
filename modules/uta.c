#include <stdlib.h>
#include "utone.h"

#define UTA_BUFSIZE 4096

int ut_uta_create(ut_uta **p)
{
    *p = malloc(sizeof(ut_uta));
    return UT_OK;
}

int ut_uta_destroy(ut_uta **p)
{
    ut_uta *pp = *p;
    ut_auxdata_free(&pp->aux);
    uta_close(&pp->uta);
    free(*p);
    return UT_OK;
}

int ut_uta_init(ut_data *ut, ut_uta *p, const char *filename)
{
    if(uta_open(ut, &p->uta, filename, UTA_READ) != UT_OK) {
        return UT_NOT_OK;
    }
    
    p->pos = 0;

    p->bufsize = UTA_BUFSIZE;
    ut_auxdata_alloc(&p->aux, sizeof(UTFLOAT) * p->bufsize);

    p->buf = p->aux.ptr;

    return UT_OK;
}

int ut_uta_compute(ut_data *ut, ut_uta *p, UTFLOAT *in, UTFLOAT *out)
{
    if(p->bufsize == 0) {
        *out = 0.0;
        return UT_OK;
    }

    if(p->pos == 0) {
        p->bufsize = uta_read_buf(ut, &p->uta, p->buf, UTA_BUFSIZE);
        if(p->bufsize == 0) {
            *out = 0.0;
            return UT_OK;
        }
    }

    *out = p->buf[p->pos];
    p->pos = (p->pos + 1) % p->bufsize;
    return UT_OK;
}
