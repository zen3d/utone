/*
 * Butterworth Filters
 *
 * This code has been extracted from the Csound butterworth filter opcodes
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): Paris Smaragdis, John ffitch
 * Year: 1994
 * Location: Opcodes/butter.c
 *
 */

#include <math.h>
#include <stdlib.h>
#include "utone.h"

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

int ut_butbr_create(ut_butbr **p)
{
    *p = malloc(sizeof(ut_butbr));
    return UT_OK;
}

int ut_butbr_destroy(ut_butbr **p)
{
    free(*p);
    return UT_OK;
}

int ut_butbr_init(ut_data *ut, ut_butbr *p)
{
    p->istor = 0.0;
    p->sr = ut->sr;
    p->freq = 1000;
    p->bw = 1000;
    p->pidsr = M_PI / ut->sr * 1.0;
    p->tpidsr = 2 * M_PI / ut->sr * 1.0;
    p->a[6] = p->a[7] = 0.0;
    p->lkf = 0.0;
    p->lkb = 0.0;
    return UT_OK;
}

int ut_butbr_compute(ut_data *ut, ut_butbr *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT *a = p->a;
    UTFLOAT t, y;

    if (p->bw <= 0.0) {
      *out = 0;
      return UT_OK;
    }

    UTFLOAT bw, fr;
    bw = p->bw;
    fr = p->freq;
    if (bw != p->lkb || fr != p->lkf) {
        UTFLOAT c, d;
        p->lkf = fr;
        p->lkb = bw;
        c = tan((UTFLOAT)(p->pidsr * bw));
        d = 2.0 * cos((UTFLOAT)(p->tpidsr * fr));
        a[1] = 1.0 / (1.0 + c);
        a[2] = - d * a[1];
        a[3] = a[1];
        a[4] = a[2];
        a[5] = (1.0 - c) * a[1];
    }
    t = (UTFLOAT)*in - a[4] * a[6] - a[5] * a[7];
    y = t * a[1] + a[2] * a[6] + a[3] * a[7];
    a[7] = a[6];
    a[6] = t;
    *out = y;
    return UT_OK;
}
