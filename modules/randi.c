/*
 * Randi
 *
 * This code has been extracted from the Csound opcode "randi".
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): Barry Vercoe, John ffitch
 * Year: 1991
 * Location: OOps/ugens4.c
 *
 * Randi needs the ftbl Soundpipe module in order to work.
 *
 */

#include <stdlib.h>
#include <math.h>
#include "utone.h"

#define ut_oneUp31Bit      (4.656612875245796924105750827168e-10)

#define ut_randGab   ((UTFLOAT)     \
        (((p->holdrand = p->holdrand * 214013 + 2531011) >> 1)  \
         & 0x7fffffff) * ut_oneUp31Bit)


int ut_randi_create(ut_randi **p)
{
    *p = malloc(sizeof(ut_randi));
    return UT_OK;
}

int ut_randi_destroy(ut_randi **p)
{
    free(*p);
    return UT_OK;
}

int ut_randi_init(ut_data *ut, ut_randi *p)
{
    p->sicvt = 1.0 * UT_FT_MAXLEN / ut->sr;
    p->phs = 0;
    p->min = 0;
    p->max = 1;
    p->cps = 3;
    p->mode = 3;
    p->holdrand = ut_rand(ut);
    p->fstval = 0;

    int mode = (int)(p->mode);
    switch (mode) {
    case 1: /* immediate interpolation between kmin and 1st random number */
        p->num1 = 0.0;
        p->num2 = ut_randGab;
        p->dfdmax = (p->num2 - p->num1) / UT_FT_MAXLEN * 1.0;
        break;
    case 2: /* immediate interpolation between ifirstval and 1st random number */
        p->num1 = (p->max - p->min) ?
          (p->fstval - p->min) / (p->max - p->min) : 0.0;
        p->num2 = ut_randGab;
        p->dfdmax = (p->num2 - p->num1) / UT_FT_MAXLEN * 1.0;
        break;
    case 3: /* immediate interpolation between 1st and 2nd random number */
        p->num1 = ut_randGab;
        p->num2 = ut_randGab;
        p->dfdmax = (p->num2 - p->num1) / UT_FT_MAXLEN * 1.0;
        break;
    default: /* old behaviour as developped by Gabriel */
        p->num1 = p->num2 = 0.0;
        p->dfdmax = 0.0;
    }
    return UT_OK;
}

int ut_randi_compute(ut_data *ut, ut_randi *p, UTFLOAT *in, UTFLOAT *out)
{
    int32_t phs = p->phs, inc;
    UTFLOAT cpsp;
    UTFLOAT amp, min;

    cpsp = p->cps;
    min = p->min;
    amp =  (p->max - min);
    inc = (int32_t)(cpsp * p->sicvt);

    *out = (p->num1 + (UTFLOAT)phs * p->dfdmax) * amp + min;
    phs += inc;
    if (phs >= UT_FT_MAXLEN) {
        phs &= UT_FT_PHMASK;
        p->num1 = p->num2;
        p->num2 = ut_randGab;
        p->dfdmax = 1.0 * (p->num2 - p->num1) / UT_FT_MAXLEN;
    }
    p->phs = phs;

    return UT_OK;
}
