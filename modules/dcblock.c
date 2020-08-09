/*
 * DCblock
 *
 * This code has been extracted from the Csound opcode "dcblock".
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): Perry R. Cook
 * Year: 1995
 * Location: Opcodes/biquad.c
 *
 */

#include <stdlib.h>
#include "utone.h"

int ut_dcblock_create(ut_dcblock **p)
{
    *p = malloc(sizeof(ut_dcblock));
    return UT_OK;
}

int ut_dcblock_destroy(ut_dcblock **p)
{
    free(*p);
    return UT_OK;
}

int ut_dcblock_init(ut_data *ut, ut_dcblock *p)
{
    p->outputs = 0.0;
    p->inputs = 0.0;
    p->gain = 0.99;
    if (p->gain == 0.0 || p->gain>=1.0 || p->gain<=-1.0)
      p->gain = 0.99;
    return UT_OK;
}

int ut_dcblock_compute(ut_data *ut, ut_dcblock *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT gain = p->gain;
    UTFLOAT outputs = p->outputs;
    UTFLOAT inputs = p->inputs;

    UTFLOAT sample = *in;
    outputs = sample - inputs + (gain * outputs);
    inputs = sample;
    *out = outputs;
    p->outputs = outputs;
    p->inputs = inputs;
    return UT_OK;
}
