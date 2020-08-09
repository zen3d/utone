/*
 * comb
 * 
 * This code has been extracted from the Csound opcode "comb".
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): Barry Vercoe, John ffitch
 * Year: 1991
 * Location: OOps/ugens6.c
 *
 */

#include <math.h>
#include <stdlib.h>
#include "utone.h"

#define log001 (-(UTFLOAT)6.9078)    /* log(.001) */

int ut_comb_create(ut_comb **p)
{
    *p = malloc(sizeof(ut_comb));
    return UT_OK;
}

int ut_comb_destroy(ut_comb **p)
{
    ut_comb *pp = *p;
    ut_auxdata_free(&pp->aux);
    free(*p);
    return UT_OK;
}

int ut_comb_init(ut_data *ut, ut_comb *p, UTFLOAT looptime)
{
    p->revtime = 3.5;
    p->looptime = looptime;
    p->bufsize = (uint32_t) (0.5 + looptime * ut->sr);
    ut_auxdata_alloc(&p->aux, p->bufsize * sizeof(UTFLOAT));
    p->prvt = 0.0;
    p->coef = 0.0;
    p->bufpos = 0;
    return UT_OK;
}

int ut_comb_compute(ut_data *ut, ut_comb *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT tmp = 0;
    UTFLOAT coef = p->coef;
    UTFLOAT outsamp = 0;
    UTFLOAT *buf = (UTFLOAT *)p->aux.ptr;

    if(p->prvt != p->revtime) {
        p->prvt = p->revtime;
        UTFLOAT exp_arg = (UTFLOAT) (log001 * p->looptime / p->prvt);
        if(exp_arg < -36.8413615) {
            coef = p->coef = 0;
        } else {
            coef = p->coef = exp(exp_arg);
        }
    }
    outsamp = buf[p->bufpos];
    tmp = outsamp;
    tmp *= coef;
    tmp += *in;
    buf[p->bufpos] = tmp;
    *out = outsamp;

    p->bufpos++;
    p->bufpos %= p->bufsize; 
    return UT_OK;
}
