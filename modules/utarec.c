#include <stdlib.h>
#include "utone.h"

#define UTA_BUFSIZE 4096

int ut_utarec_create(ut_utarec **p)
{
    *p = malloc(sizeof(ut_utarec));
    return UT_OK;
}

int ut_utarec_destroy(ut_utarec **p)
{
    ut_utarec *pp = *p;
    ut_auxdata_free(&pp->aux);
    uta_close(&pp->uta);
    free(*p);
    return UT_OK;
}

int ut_utarec_init(ut_data *ut, ut_utarec *p, const char *filename)
{
    if(uta_open(ut, &p->uta, filename, UTA_WRITE) != UT_OK) {
        return UT_NOT_OK;
    }
    
    p->pos = UTA_BUFSIZE;

    p->bufsize = UTA_BUFSIZE;
    ut_auxdata_alloc(&p->aux, sizeof(UTFLOAT) * p->bufsize);

    p->buf = p->aux.ptr;
    return UT_OK;
}

int ut_utarec_compute(ut_data *ut, ut_utarec *p, UTFLOAT *in, UTFLOAT *out)
{
    if(p->pos == 0) {
        p->pos = p->bufsize;
        uta_write_buf(ut, &p->uta, p->buf, p->bufsize);
    }

    p->buf[p->bufsize - p->pos] = *in;

    p->pos--;
    *out = *in;
    return UT_OK;
}

/* call this to close utarec. will write the rest of the buffer */
int ut_utarec_close(ut_data *ut, ut_utarec *p)
{
    if(p->pos < p->bufsize - 1) {
        uta_write_buf(ut, &p->uta, p->buf, p->bufsize - p->pos);
    }
    return UT_OK;
}
