/*
 * Port
 * 
 * This code has been extracted from the Csound opcode "portk".
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): Robbin Whittle, John ffitch
 * Year: 1995, 1998
 * Location: Opcodes/biquad.c
 *
 */


#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#define ROOT2 (1.4142135623730950488)

#ifndef M_PI
#define M_PI		3.14159265358979323846	
#endif 

#include "utone.h"

int ut_port_create(ut_port **p)
{
    *p = malloc(sizeof(ut_port));
    return UT_OK;
}

int ut_port_destroy(ut_port **p)
{
    free(*p);
    return UT_OK;
}

int ut_port_init(ut_data *ut, ut_port *p, UTFLOAT htime)
{
    p->yt1 = 0;
    p->prvhtim = -100.0;
    p->htime = htime;

    p->sr = ut->sr;
    p->onedsr = 1.0/p->sr;
    return UT_OK;
}

int ut_port_compute(ut_data *ut, ut_port *p, UTFLOAT *in, UTFLOAT *out)
{
    if(p->prvhtim != p->htime){
        p->c2 = pow(0.5, p->onedsr / p->htime);
        p->c1 = 1.0 - p->c2;
        p->prvhtim = p->htime;
    }

    *out = p->yt1 = p->c1 * *in + p->c2 * p->yt1;
    return UT_OK;
}

int ut_port_reset(ut_data *ut, ut_port *p, UTFLOAT *in)
{
    p->yt1 = *in;
    return UT_OK;
}
