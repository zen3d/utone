/*
 * Pan2
 * 
 * This code has been extracted from the Csound opcode "pan2"
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): John ffitch
 * Year: 2007
 * Location: Opcodes/pan2.c
 *
 */

#include <stdlib.h>
#include <math.h>
#include "utone.h"

#ifndef M_PI
#define M_PI		3.14159265358979323846	
#endif 

#define SQRT2 1.41421356237309504880


int ut_pan2_create(ut_pan2 **p)
{
    *p = malloc(sizeof(ut_pan2));
    return UT_OK;
}

int ut_pan2_destroy(ut_pan2 **p)
{
    free(*p);
    return UT_OK;
}

int ut_pan2_init(ut_data *ut, ut_pan2 *p)
{
    p->type = 0;
    p->pan = 0;
    return UT_OK;
}

int ut_pan2_compute(ut_data *ut, ut_pan2 *p, UTFLOAT *in, UTFLOAT *out1, UTFLOAT *out2)
{
    /* Send the signal's input to the output */
    uint32_t type = p->type;
    UTFLOAT pan = (1 + p->pan) * 0.5;
    UTFLOAT cc, ss, l, r;

    type %= 4;

    switch (type) {
        /* Equal power */
        case 0:
        pan = M_PI * 0.5 * pan;
        *out1 = *in * cos(pan);
        *out2 = *in * sin(pan);
        break;

        /* Square root */
        case 1:
        *out1 = *in * sqrt(pan);
        *out2 = *in * sqrt(1.0 - pan);
        break;

        /* simple linear */
        case 2:
        *out1 = *in * (1.0 - pan);
        *out2 = *in * pan;
        break;

        /* Equal power (alternative) */
        case 3:

        cc = cos(M_PI * pan * 0.5);
        ss = sin(M_PI * pan * 0.5);
        l = SQRT2 * (cc + ss) * 0.5;
        r = SQRT2 * (cc - ss) * 0.5;
        *out1 = *in * l;
        *out2 = *in * r;
        break;
    }

    return UT_OK;
}
