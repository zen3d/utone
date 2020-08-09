/*
 * Dust
 * 
 * This code has been extracted from the Csound opcode "dust".
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): Tito Latini
 * Year: 2012
 * Location: Opcodes/tl/sc_noise.c
 *
 */


#include <stdlib.h>
#include "utone.h"

int ut_dust_create(ut_dust **p)
{
    *p = malloc(sizeof(ut_dust));
    return UT_OK;
}

int ut_dust_destroy(ut_dust **p) 
{
    free(*p);
    return UT_OK;
}

int ut_dust_init(ut_data *ut, ut_dust *p) 
{
    p->density = 10;
    p->amp = 0.4;
    p->density0 = 0.0;
    p->thresh = 0.0;
    p->scale = 0.0;
    p->rand = ut_rand(ut);
    p->onedsr = 1.0 / ut->sr;
    p->bipolar = 0;
    return UT_OK;
}

int ut_dust_compute(ut_data *ut, ut_dust *p, UTFLOAT *in, UTFLOAT *out) 
{
    UTFLOAT density, thresh, scale;
    const UTFLOAT dv2_31 = 4.656612873077392578125e-10;
    density = p->density;
    if (density != p->density0) {
        thresh = p->thresh = density * p->onedsr;
        if(p->bipolar) {
            scale  = p->scale  = (thresh > 0.0 ? 2.0 / thresh : 0.0);
        } else {
            scale  = p->scale  = (thresh > 0.0 ? 1.0 / thresh : 0.0);
        }
        p->density0 = density;
    } else {
        thresh = p->thresh;
        scale  = p->scale;
    }
    *out = 0;
    UTFLOAT r;
    p->rand = ut_rand(ut);
    r = (UTFLOAT)p->rand * dv2_31;

    if(p->bipolar) {
        *out = p->amp * (r < thresh ? r*scale - 1.0 : 0.0);
    } else {
        *out = p->amp * (r < thresh ? r*scale : 0.0);
    }

    return UT_OK;
}
