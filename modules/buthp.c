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
#include <stdint.h>
#include <stdlib.h>
#define ROOT2 (1.4142135623730950488)

#ifndef M_PI
#define M_PI		3.14159265358979323846	/* pi */
#endif

#include "utone.h"

/* Filter loop */

static int ut_butter_filter(UTFLOAT *in, UTFLOAT *out, UTFLOAT *a)
{
    UTFLOAT t, y;
    t = *in - a[4] * a[6] - a[5] * a[7];
    y = t * a[1] + a[2] * a[6] + a[3] * a[7];
    a[7] = a[6];
    a[6] = t;
    *out = y;
    return UT_OK;
}


int ut_buthp_create(ut_buthp **p)
{
    *p = malloc(sizeof(ut_buthp));
    return UT_OK;
}

int ut_buthp_destroy(ut_buthp **p)
{
    free(*p);
    return UT_OK;
}

int ut_buthp_init(ut_data *ut, ut_buthp *p)
{
    p->istor = 0.0;
    p->sr = ut->sr;
    p->freq = 1000;
    p->pidsr = M_PI / ut->sr * 1.0;
    if (p->istor==0.0) {
        p->a[6] = p->a[7] = 0.0;
        p->lkf = 0.0;
    }
    return UT_OK;
}

int ut_buthp_compute(ut_data *ut, ut_buthp *p, UTFLOAT *in, UTFLOAT *out)
{
    if (p->freq <= 0.0)     {
      *out = 0;
      return UT_OK;
    }

    if (p->freq != p->lkf)      {
      UTFLOAT *a, c;
      a = p->a;
      p->lkf = p->freq;
      c = tan((UTFLOAT)(p->pidsr * p->lkf));

      a[1] = 1.0 / ( 1.0 + ROOT2 * c + c * c);
      a[2] = -(a[1] + a[1]);
      a[3] = a[1];
      a[4] = 2.0 * ( c*c - 1.0) * a[1];
      a[5] = ( 1.0 - ROOT2 * c + c * c) * a[1];
    }
    ut_butter_filter(in, out, p->a);
    return UT_OK;
}

