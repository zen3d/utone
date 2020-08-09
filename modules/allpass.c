/*
 * Allpass
 * 
 * This code has been extracted from the Csound opcode "allpass".
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): Barry Vercoe, John ffitch
 * Year: 1991
 * Location: Opcodes/ugens6.c
 *
 */

#include <math.h>
#include <stdlib.h>
#include "utone.h"

int ut_allpass_create(ut_allpass **p)
{
    *p = malloc(sizeof(ut_allpass));
    return UT_OK;
}

int ut_allpass_destroy(ut_allpass **p)
{
    ut_allpass *pp = *p;
    ut_auxdata_free(&pp->aux);
    free(*p);
    return UT_OK;
}

int ut_allpass_init(ut_data *ut, ut_allpass *p, UTFLOAT looptime)
{
    p->revtime = 3.5;
    p->looptime = looptime;
    p->bufsize = 0.5 + looptime * ut->sr;
    ut_auxdata_alloc(&p->aux, p->bufsize * sizeof(UTFLOAT));
    p->prvt = 0.0;
    p->coef = 0.0;
    p->bufpos = 0;
    return UT_OK;
}

int ut_allpass_compute(ut_data *ut, ut_allpass *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT y, z;
    UTFLOAT coef = p->coef;
    UTFLOAT *buf = (UTFLOAT *)p->aux.ptr;
    if(p->prvt != p->revtime) {
        p->prvt = p->revtime;
        coef = p->coef = exp(-6.9078 * p->looptime / p->prvt);
    }
    y = buf[p->bufpos];
    z = coef * y + *in; 
    buf[p->bufpos] = z;
    *out = y - coef * z;

    p->bufpos++;
    p->bufpos %= p->bufsize; 
    return UT_OK;
}
