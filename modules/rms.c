/*
 * RMS
 * 
 * This code has been extracted from the Csound opcode "rms".
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): Barry Vercoe, John ffitch, Gabriel Maldonado
 * Year: 1991
 * Location: Opcodes/ugens5.c
 *
 */

#include <stdlib.h>
#include <math.h>
#include "utone.h"

#ifndef M_PI
#define M_PI		3.14159265358979323846	
#endif 

int ut_rms_create(ut_rms **p)
{
    *p = malloc(sizeof(ut_rms));
    return UT_OK;
}

int ut_rms_destroy(ut_rms **p)
{
    free(*p);
    return UT_OK;
}

int ut_rms_init(ut_data *ut, ut_rms *p)
{
    p->ihp = 10;
    p->istor = 0;

    UTFLOAT b;

    b = 2.0 - cos((UTFLOAT)(p->ihp * (2 * M_PI / ut->sr)));
    p->c2 = b - sqrt(b*b - 1.0);
    p->c1 = 1.0 - p->c2;
    if (!p->istor) p->prvq = 0.0;
    return UT_OK;
}

int ut_rms_compute(ut_data *ut, ut_rms *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT q;
    UTFLOAT c1 = p->c1, c2 = p->c2;

    q = p->prvq;
    
    UTFLOAT as = *in;
    q = c1 * as * as + c2 * q;
    
    p->prvq = q;
    *out = sqrt(q);
    return UT_OK;
}
