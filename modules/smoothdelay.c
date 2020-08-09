#include <stdlib.h>
#include "utone.h"

#ifndef max
#define max(a, b) ((a > b) ? a : b)
#endif

#ifndef min
#define min(a, b) ((a < b) ? a : b)
#endif


int ut_smoothdelay_create(ut_smoothdelay **p)
{
    *p = malloc(sizeof(ut_smoothdelay));
    return UT_OK;
}

int ut_smoothdelay_destroy(ut_smoothdelay **p)
{
    ut_smoothdelay *pp = *p;
    ut_auxdata_free(&pp->buf1);
    ut_auxdata_free(&pp->buf2);
    free(*p);
    return UT_OK;
}

int ut_smoothdelay_init(ut_data *ut, ut_smoothdelay *p, 
        UTFLOAT maxdel, uint32_t interp)
{
    uint32_t n = (int32_t)(maxdel * ut->sr)+1;
    p->sr = ut->sr;
    p->del = maxdel * 0.5;
    p->pdel = -1;
    p->maxdel = maxdel;
    p->feedback = 0;
    p->maxbuf = n - 1;
    p->maxcount = interp;

    ut_auxdata_alloc(&p->buf1, n * sizeof(UTFLOAT));
    p->bufpos1 = 0;
    p->deltime1 = (uint32_t) (p->del * ut->sr);

    ut_auxdata_alloc(&p->buf2, n * sizeof(UTFLOAT));
    p->bufpos2 = 0;
    p->deltime2 = p->deltime1;

    p->counter = 0;
    p->curbuf = 0;
    return UT_OK;
}

static UTFLOAT delay_sig(UTFLOAT *buf, 
        uint32_t *bufpos, 
        uint32_t deltime, 
        UTFLOAT fdbk, 
        UTFLOAT in)
{
    UTFLOAT delay = buf[*bufpos];
    UTFLOAT sig = (delay * fdbk) + in;
    buf[*bufpos] = sig;
    *bufpos = (*bufpos + 1) % deltime;
    return delay;
}

int ut_smoothdelay_compute(ut_data *ut, ut_smoothdelay *p, UTFLOAT *in, UTFLOAT *out)
{
    *out = 0;
    if(p->del != p->pdel && p->counter == 0) {
        uint32_t dels = min((uint32_t)(p->del * ut->sr), p->maxbuf);

        /* initial delay time sets time for both buffers */

        if(p->pdel < 0) {
            p->deltime1 = dels;
            p->deltime2 = dels;
        }

        p->pdel = p->del;

        if(dels == 0) dels = 1;

        if(p->curbuf == 0) {
            p->curbuf = 1;
            p->deltime2 = dels;
        } else {
            p->curbuf = 0;
            p->deltime1 = dels;
        }
        p->counter = p->maxcount;
    }



    UTFLOAT *buf1 = (UTFLOAT *)p->buf1.ptr; 
    UTFLOAT *buf2 = (UTFLOAT *)p->buf2.ptr; 
    UTFLOAT it = (UTFLOAT)p->counter / p->maxcount;
    if(p->counter != 0) p->counter--;
  
    UTFLOAT del1 = delay_sig(buf1, &p->bufpos1, 
            p->deltime1, p->feedback, *in);

    UTFLOAT del2 = delay_sig(buf2, &p->bufpos2, 
            p->deltime2, p->feedback, *in);

    if(p->curbuf == 0) {
        /* 1 to 2 */
        *out = (del1 * it) + (del2 * (1 - it));
    } else {
        /* 2 to 1 */
        *out = (del2 * it) + (del1 * (1 - it));
    }
    return UT_OK;
}
