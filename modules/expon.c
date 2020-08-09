/*
 * Expon
 *
 * This code has been extracted from the Csound opcode "expon".
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): Barry Vercoe
 * Year: 1991
 * Location: OOps/ugens1.c
 *
 */

#include <math.h>
#include <stdlib.h>
#include "utone.h"

int ut_expon_create(ut_expon **p)
{
    *p = malloc(sizeof(ut_expon));
    return UT_OK;
}

int ut_expon_destroy(ut_expon **p)
{
    free(*p);
    return UT_OK;
}

static void expon_reinit(ut_data *ut, ut_expon *p)
{
    p->stime = 0;
    p->sdur = p->dur * ut->sr;
    UTFLOAT onedsr = 1.0 / ut->sr;
    if((p->a * p->b) > 0.0) {
        p->incr = pow((UTFLOAT)(p->b / p->a), onedsr / p->dur);
    } else {
        fprintf(stderr, "Warning: p values must be non-zero\n");
        p->incr = 1;
        p->val = p->a;
    }

    p->val = p->a;
}

int ut_expon_init(ut_data *ut, ut_expon *p)
{
    p->a = 0.000001;
    p->b = 1;
    p->dur = 1;
    expon_reinit(ut, p);
    p->init = 1;
    return UT_OK;
}

int ut_expon_compute(ut_data *ut, ut_expon *p, UTFLOAT *in, UTFLOAT *out)
{
    if(*in) {
        expon_reinit(ut, p);
        p->init = 0;
    }

    if(p->init) {
        *out = 0;
        return UT_OK;
    }

    if(p->stime < p->sdur) {
        UTFLOAT val = p->val;
        p->val *= p->incr;
        p->stime++;
        *out = val;
    } else {
        *out = p->b;
    }
    return UT_OK;
}
