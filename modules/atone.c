/*
 * ATone
 * 
 * This code has been extracted from the Csound opcode "atone".
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): Barry Vercoe, John FFitch, Gabriel Maldonado
 * Year: 1991
 * Location: OOps/ugens5.c
 *
 */

#include <stdlib.h>
#include <math.h>
#include "utone.h"

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif 

int ut_atone_create(ut_atone **p)
{
    *p = malloc(sizeof(ut_atone));
    return UT_OK;
}

int ut_atone_destroy(ut_atone **p)
{
    free(*p);
    return UT_OK;
}

int ut_atone_init(ut_data *ut, ut_atone *p)
{
    p->hp = 1000;
    UTFLOAT b;
    p->tpidsr = (2.0 * M_PI) / ut->sr * 1.0;
    p->prvhp = (UTFLOAT)p->hp;
    b = 2.0 - cos((UTFLOAT)(p->prvhp * p->tpidsr));
    p->c2 = b - sqrt(b * b - 1.0);
    p->c1 = 1.0 - p->c2;
    p->yt1 = 0.0;
    return UT_OK;
}

int ut_atone_compute(ut_data *ut, ut_atone *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT c2 = p->c2, yt1 = p->yt1;
    UTFLOAT x;

    if (p->hp != p->prvhp) {
      UTFLOAT b;
      p->prvhp = p->hp;
      b = 2.0 - cos((UTFLOAT)(p->hp * p->tpidsr));
      p->c2 = c2 = b - sqrt(b * b - 1.0);
    }

    x = yt1 = c2 * (yt1 + *in);
    *out = x;
    yt1 -= *in;
    p->yt1 = yt1;
    return UT_OK;
}
