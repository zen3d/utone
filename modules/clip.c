/*
 * Clip
 * 
 * This code has been extracted from the Csound opcode "clip".
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): John ffitch, Istvan Varga, Peter Neubäcker,
                       rasmus ekman, Phil Burk
 * Year: 1999
 * Location: Opcodes/pitch.c
 *
 */

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif 

#include "utone.h"

int ut_clip_create(ut_clip **p)
{
    *p = malloc(sizeof(ut_clip));
    return UT_OK;
}

int ut_clip_destroy(ut_clip **p)
{
    free(*p);
    return UT_OK;
}

int ut_clip_init(ut_data *ut, ut_clip *p)
{
    p->lim = 1;
    p->k1 = M_PI / (2.0 * p->lim);
    return UT_OK;
}

int ut_clip_compute(ut_data *ut, ut_clip *p, UTFLOAT *in, UTFLOAT *out)
{
    p->k1 = M_PI / (2.0 * p->lim);
    UTFLOAT k1 = p->k1;
    UTFLOAT limit = p->lim;
    UTFLOAT x;

    x = *in;
    if (x >= limit) {
        x = limit;
    } else if (x <= -limit) {
        x = -limit;
    } else {
        x = limit * sin(k1 * x);
    }
    *out = x;

    return UT_OK;
}
