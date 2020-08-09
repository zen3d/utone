/*
 * Phasor
 * 
 * This code has been extracted from the Csound opcode "phasor".
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): Barry Vercoe, John ffitch, Robin whittle
 * Year: 1991
 * Location: OOps/ugens2.c
 *
 */

#include <stdlib.h>
#include "utone.h"

int ut_phasor_create(ut_phasor **p)
{
    *p = malloc(sizeof(ut_phasor));
    return UT_OK;
}

int ut_phasor_destroy(ut_phasor **p)
{
    free(*p);
    return UT_OK;
}

int ut_phasor_init(ut_data *ut, ut_phasor *p, UTFLOAT iphs)
{
    p->freq = 440;
    p->phs = iphs;
    p->curphs = iphs;
    p->onedsr = 1.0 / ut->sr;
    return UT_OK;
}

int ut_phasor_compute(ut_data *ut, ut_phasor *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT phase;
    UTFLOAT incr;

    phase = p->curphs;
    incr = p->freq * p->onedsr;
    *out = phase;
    phase += incr;
    if (phase >= 1.0) {
        phase -= 1.0;
    } else if (phase < 0.0) {
        phase += 1.0;
    }
    p->curphs = phase;
    return UT_OK;
}
