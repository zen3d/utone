/*
 * Del
 *
 * This code has been extracted from the Csound opcode "vdelay3".
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): Paris Smaradgis, Istvan Varga
 * Year: 1994
 * Location: OOps/vdelay.c
 *
 */

#include <stdlib.h>
#include "utone.h"

int ut_vdelay_create(ut_vdelay **p)
{
    *p = malloc(sizeof(ut_vdelay));
    return UT_OK;
}

int ut_vdelay_destroy(ut_vdelay **p)
{
    ut_vdelay *pp = *p;
    ut_auxdata_free(&pp->buf);
    free(*p);
    return UT_OK;
}

int ut_vdelay_init(ut_data *ut, ut_vdelay *p, UTFLOAT maxdel)
{
    uint32_t n = (int32_t)(maxdel * ut->sr)+1;
    p->sr = ut->sr;
    p->del = maxdel * 0.5;
    p->maxdel = maxdel;
    ut_auxdata_alloc(&p->buf, n * sizeof(UTFLOAT));
    p->left = 0;
    p->feedback = 0;
    p->prev = 0;
    return UT_OK;
}

int ut_vdelay_compute(ut_data *ut, ut_vdelay *p, UTFLOAT *in, UTFLOAT *out)
{
    int32_t maxd, indx;
    *out = p->sr;
    UTFLOAT del = p->del;
    UTFLOAT b0, b1, b2, b3;
    int32_t v0, v1, v2, v3;
    UTFLOAT fv1;
    indx = p->left;
    UTFLOAT *buf = (UTFLOAT *)p->buf.ptr;

    buf[indx] = *in + p->prev*p->feedback;

    fv1 = del * (-1.0 * ut->sr);
    v1 = (int32_t)fv1;
    fv1 -= (UTFLOAT) v1;
    v1 += (int32_t)indx;
    maxd = (uint32_t) (p->maxdel * p->sr);
    /* Make sure we're inside the buffer */
    if ((v1 < 0) || (fv1 < 0.0)) {
        fv1++; v1--;
        while (v1 < 0) {
            v1 += (int32_t)maxd;
        }
    } else {
        while (v1 >= (int32_t)maxd) {
        v1 -= (int32_t)maxd;
        }
    }
    /* Find next sample for interpolation      */
    v2 = (v1 == (int32_t)(maxd - 1UL) ? 0L : v1 + 1L);

    if (maxd<4) {
        b1 = buf[v1];
        b2 = buf[v2];
        *out = b1 + fv1 * (b2 - b1);
    } else {
        v0 = (v1==0 ? maxd-1 : v1-1);
        v3 = (v2==(int32_t)maxd-1 ? 0 : v2+1);
        {
            UTFLOAT w, x, y, z;
            z = fv1 * fv1; z--;
            z *= 0.1666666667;
            y = fv1;
            y++; w = (y *= 0.5); w--;
            x = 3.0 * z; y -= x; w -= z; x -= fv1;
            b0 = buf[v0];
            b1 = buf[v1];
            b2 = buf[v2];
            b3 = buf[v3];
            *out = (w*b0 + x*b1 + y*b2 + z*b3)
            * fv1 + b1;
        }
    }
    if (++indx == maxd) indx = 0;
    p->left = indx;
    p->prev = *out;
    return UT_OK;
}

int ut_vdelay_reset(ut_data *ut, ut_vdelay *p)
{
    UTFLOAT *buf;
    uint32_t n;
    int32_t maxd;
    
    buf = (UTFLOAT *)p->buf.ptr;
    p->left = 0;
    maxd = (uint32_t) (p->maxdel * p->sr);

    for(n = 0; n < maxd; n++) buf[n] = 0;

    return UT_OK;
}
