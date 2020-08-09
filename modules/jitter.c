/*
 * Jitter
 * 
 * This code has been extracted from the Csound opcode "jitter".
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): Gabriel Maldonado
 * Year: 1998
 * Location: Opcodes/uggab.c
 *
 */

#include <stdlib.h>
#include "utone.h"

/* the randgabs are essentially magic incantations from Csound */

static UTFLOAT ut_jitter_randgab(ut_data *ut) 
{
    UTFLOAT out = (UTFLOAT) ((ut_rand(ut) >> 1) & 0x7fffffff) *
    (4.656612875245796924105750827168e-10);
    return out;
}

static UTFLOAT ut_jitter_birandgab(ut_data *ut) 
{
    UTFLOAT out = (UTFLOAT) (ut_rand(ut) & 0x7fffffff) *
    (4.656612875245796924105750827168e-10);
    return out;
}

int ut_jitter_create(ut_jitter **p)
{
    *p = malloc(sizeof(ut_jitter));
    return UT_OK;
}

int ut_jitter_destroy(ut_jitter **p)
{
    free(*p);
    return UT_OK;
}

int ut_jitter_init(ut_data *ut, ut_jitter *p)
{
    p->amp = 0.5;
    p->cpsMin = 0.5;
    p->cpsMax = 4; 
    p->num2 = ut_jitter_birandgab(ut);
    p->initflag = 1;
    p->phs=0;
    return UT_OK;
}

int ut_jitter_compute(ut_data *ut, ut_jitter *p, UTFLOAT *in, UTFLOAT *out)
{
    if (p->initflag) {
      p->initflag = 0;
      *out = p->num2 * p->amp;
      p->cps = ut_jitter_randgab(ut) * (p->cpsMax - p->cpsMin) + p->cpsMin;
      p->phs &= UT_FT_PHMASK;
      p->num1 = p->num2;
      p->num2 = ut_jitter_birandgab(ut);
      p->dfdmax = 1.0 * (p->num2 - p->num1) / UT_FT_MAXLEN;
      return UT_OK;
    }
    
    *out = (p->num1 + (UTFLOAT)p->phs * p->dfdmax) * p->amp;
    p->phs += (int32_t)(p->cps * (UTFLOAT)(UT_FT_MAXLEN / ut->sr));

    if (p->phs >= UT_FT_MAXLEN) {
      p->cps   = ut_jitter_randgab(ut) * (p->cpsMax - p->cpsMin) + p->cpsMin;
      p->phs   &= UT_FT_PHMASK;
      p->num1   = p->num2;
      p->num2 =  ut_jitter_birandgab(ut);
      p->dfdmax = 1.0 * (p->num2 - p->num1) / UT_FT_MAXLEN;
    }
    return UT_OK;
}
