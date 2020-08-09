/*
 * Bal
 *
 * This code has been extracted from the Csound opcode "balance".
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): Barry Vercoe, john ffitch, Gabriel Maldonado
 * Year: 1991
 * Location: OOps/ugens5.c
 *
 */

#include <math.h>
#include <stdlib.h>
#include "utone.h"

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

int ut_bal_create(ut_bal **p)
{
    *p = malloc(sizeof(ut_bal));
    return UT_OK;
}

int ut_bal_destroy(ut_bal **p)
{
    free(*p);
    return UT_OK;
}

int ut_bal_init(ut_data *ut, ut_bal *p)
{

    UTFLOAT b;
    p->ihp = 10;
    b = 2.0 - cos((UTFLOAT)(p->ihp * (2.0 * M_PI / ut->sr)));
    p->c2 = b - sqrt(b*b - 1.0);
    p->c1 = 1.0 - p->c2;
    p->prvq = p->prvr = p->prva = 0.0;

    return UT_OK;
}

int ut_bal_compute(ut_data *ut, ut_bal *p, UTFLOAT *sig, UTFLOAT *comp, UTFLOAT *out)
{
    UTFLOAT q, r, a, diff;
    UTFLOAT c1 = p->c1, c2 = p->c2;

    q = p->prvq;
    r = p->prvr;
    UTFLOAT as = *sig;
    UTFLOAT cs = *comp;

    q = c1 * as * as + c2 * q;
    r = c1 * cs * cs + c2 * r;

    p->prvq = q;
    p->prvr = r;

    if (q != 0.0) {
        a = sqrt(r/q);
    } else {
        a = sqrt(r);
    }

    if((diff = a - p->prva) != 0.0) {
        *out = *sig * p->prva;
        p->prva = a;
    } else {
        *out = *sig * a;
    }

    return UT_OK;
}
