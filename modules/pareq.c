/*
 * Pareq
 * 
 * This code has been extracted from the Csound opcode "pareq".
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s):  Hans Mikelson, Matt Gerassimoff, 
*                       Jens Groh, John ffitch, Steven Yi
 * Year: 2001
 * Location: Opcodes/biquad.c
 *
 */

#include <stdlib.h>
#include <math.h>
#include "utone.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif 

int ut_pareq_create(ut_pareq **p)
{
    *p = malloc(sizeof(ut_pareq));
    return UT_OK;
}

int ut_pareq_destroy(ut_pareq **p)
{
    free(*p);
    return UT_OK;
}

int ut_pareq_init(ut_data *ut, ut_pareq *p)
{
    p->q = 0.707;
    p->v = 1;
    p->mode = 0;
    p->fc = 1000;

    p->xnm1 = p->xnm2 = p->ynm1 = p->ynm2 = 0.0;
    p->prv_fc = p->prv_v = p->prv_q = -1.0;
    p->tpidsr = (2 * M_PI) / ut->sr;
    return UT_OK;
}

int ut_pareq_compute(ut_data *ut, ut_pareq *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT xn, yn;
    UTFLOAT sq;

    if (p->fc != p->prv_fc || p->v != p->prv_v || p->q != p->prv_q) {
        UTFLOAT omega = (UTFLOAT)(p->tpidsr * p->fc), k, kk, vkk, vk, vkdq, a0;
        p->prv_fc = p->fc; p->prv_v = p->v; p->prv_q = p->q;
        switch ((int)p->mode) {
            /* Low Shelf */
            case 1: 
                sq = sqrt(2.0 * (UTFLOAT) p->prv_v);
                k = tan(omega * 0.5);
                kk = k * k;
                vkk = (UTFLOAT)p->prv_v * kk;
                p->b0 = 1.0 + sq * k + vkk;
                p->b1 = 2.0 * (vkk - 1.0);
                p->b2 = 1.0 - sq * k + vkk;
                a0 = 1.0 + k / (UTFLOAT)p->prv_q + kk;
                p->a1 = 2.0 * (kk - 1.0);
                p->a2 = 1.0 - k / (UTFLOAT)p->prv_q + kk;
                break;

            /* High Shelf */
            case 2: 
                sq = sqrt(2.0 * (UTFLOAT) p->prv_v);
                k = tan((M_PI - omega) * 0.5);
                kk = k * k;
                vkk = (UTFLOAT)p->prv_v * kk;
                p->b0 = 1.0 + sq * k + vkk;
                p->b1 = -2.0 * (vkk - 1.0);
                p->b2 = 1.0 - sq * k + vkk;
                a0 = 1.0 + k / (UTFLOAT)p->prv_q + kk;
                p->a1 = -2.0 * (kk - 1.0);
                p->a2 = 1.0 - k / (UTFLOAT)p->prv_q + kk;
                break;

            /* Peaking EQ */
            default: 
                k = tan(omega * 0.5);
                kk = k * k;
                vk = (UTFLOAT)p->prv_v * k;
                vkdq = vk / (UTFLOAT)p->prv_q;
                p->b0 = 1.0 + vkdq + kk;
                p->b1 = 2.0 * (kk - 1.0);
                p->b2 = 1.0 - vkdq + kk;
                a0 = 1.0 + k / (UTFLOAT)p->prv_q + kk;
                p->a1 = 2.0 * (kk - 1.0);
                p->a2 = 1.0 - k / (UTFLOAT)p->prv_q + kk;
        }
        a0 = 1.0 / a0;
        p->a1 *= a0; p->a2 *= a0; p->b0 *= a0; p->b1 *= a0; p->b2 *= a0;
    }
    {
        UTFLOAT a1 = p->a1, a2 = p->a2;
        UTFLOAT b0 = p->b0, b1 = p->b1, b2 = p->b2;
        UTFLOAT xnm1 = p->xnm1, xnm2 = p->xnm2, ynm1 = p->ynm1, ynm2 = p->ynm2;
        xn = *in;
        yn = b0 * xn + b1 * xnm1 + b2 * xnm2 - a1 * ynm1 - a2 * ynm2;
        xnm2 = xnm1;
        xnm1 = xn;
        ynm2 = ynm1;
        ynm1 = yn;
        *out = yn;
        p->xnm1 = xnm1; p->xnm2 = xnm2; p->ynm1 = ynm1; p->ynm2 = ynm2;
    }
    return UT_OK;
}
