/*
 * Mode 
 * 
 * This code has been extracted from the Csound opcode "mode".
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): Francois Blanc, Steven Yi
 * Year: 2001
 * Location: Opcodes/biquad.c
 *
 */

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#define ROOT2 (1.4142135623730950488)

#ifndef M_PI
#define M_PI		3.14159265358979323846	/* pi */
#endif 

#include "utone.h"

int ut_mode_create(ut_mode **p)
{
    *p = malloc(sizeof(ut_mode));
    return UT_OK;
}

int ut_mode_destroy(ut_mode **p)
{
    free(*p);
    return UT_OK;
}

int ut_mode_init(ut_data *ut, ut_mode *p)
{
    p->freq = 500.0;
    p->q = 50;

    p->xnm1 = p->ynm1 = p->ynm2 = 0.0;
    p->a0 = p->a1 = p->a2 = p->d = 0.0;
    p->lfq = -1.0;
    p->lq = -1.0;

    p->sr = ut->sr;

    return UT_OK;
}

int ut_mode_compute(ut_data *ut, ut_mode *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT lfq = p->lfq, lq = p->lq;

    UTFLOAT xn, yn, a0=p->a0, a1=p->a1, a2=p->a2,d=p->d;
    UTFLOAT xnm1 = p->xnm1, ynm1 = p->ynm1, ynm2 = p->ynm2;

    UTFLOAT kfq = p->freq;
    UTFLOAT kq  = p->q;
    if (lfq != kfq || lq != kq) {
        UTFLOAT kfreq  = kfq*(2.0 * M_PI);
        UTFLOAT kalpha = (p->sr/kfreq);
        UTFLOAT kbeta  = kalpha*kalpha;
               d      = 0.5*kalpha;

        lq = kq; lfq = kfq;
        a0     = 1.0/ (kbeta+d/kq);
        a1     = a0 * (1.0-2.0*kbeta);
        a2     = a0 * (kbeta-d/kq);
     }
     xn = *in;

     yn = a0*xnm1 - a1*ynm1 - a2*ynm2;

     xnm1 = xn;
     ynm2 = ynm1;
     ynm1 = yn;

     yn = yn*d;

     *out  = yn;

    p->xnm1 = xnm1;  p->ynm1 = ynm1;  p->ynm2 = ynm2;
    p->lfq = lfq;    p->lq = lq;      p->d = d;
    p->a0 = a0;      p->a1 = a1;      p->a2 = a2;
    return UT_OK;
}
