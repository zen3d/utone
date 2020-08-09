/*
 * Dist
 * 
 * This code has been extracted from the Csound opcode "distort1".
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): Hans Mikelson
 * Year: 1998
 * Location: Opcodes/biquad.c
 *
 */

#include <math.h>
#include <stdlib.h>
#include "utone.h"

int ut_dist_create(ut_dist **p)
{
    *p = malloc(sizeof(ut_dist));
    return UT_OK;
}

int ut_dist_destroy(ut_dist **p)
{
    free(*p);
    return UT_OK;
}

int ut_dist_init(ut_data *ut, ut_dist *p)
{
    p->pregain = 2.0;
    p->postgain = 0.5;
    p->shape1 = 0;
    p->shape2 = 0;
    return UT_OK;
}

int ut_dist_compute(ut_data *ut, ut_dist *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT pregain = p->pregain, postgain  = p->postgain;
    UTFLOAT shape1 = p->shape1, shape2 = p->shape2;
    UTFLOAT sig;
    
    pregain   *=  6.5536;
    postgain  *=  0.61035156;
    shape1    *=  4.096;
    shape2    *=  4.096;

    /* IV - Dec 28 2002 */
    shape1 += pregain;
    shape2 -= pregain;
    postgain *= 0.5;
    sig = *in;
    /* Generate tanh distortion and output the result */
    *out =                          
    ((exp(sig * shape1) - exp(sig * shape2))
             / cosh(sig * pregain))
    * postgain;
    return UT_OK;
}
