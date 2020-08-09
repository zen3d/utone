/*
 * Tone
 *
 * This code has been extracted from the Csound opcode "tone".
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): Barry Vercoe, John FFitch, Gabriel Maldonado
 * Year: 1991
 * Location: OOps/ugens5.c
 *
 */

#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

#include "utone.h"


int ut_tone_create(ut_tone **t)
{
    *t = malloc(sizeof(ut_tone));
    return UT_OK;
}

int ut_tone_destroy(ut_tone **t)
{
    free(*t);
    return UT_OK;
}

int ut_tone_init(ut_data *ut, ut_tone *p)
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

int ut_tone_compute(ut_data *ut, ut_tone *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT c1 = p->c1, c2 = p->c2;
    UTFLOAT yt1 = p->yt1;

    if (p->hp != p->prvhp) {
      UTFLOAT b;
      p->prvhp = p->hp;
      b = 2.0 - cos((p->prvhp * p->tpidsr));
      p->c2 = c2 = b - sqrt(b * b - 1.0);
      p->c1 = c1 = 1.0 - c2;
    }

    yt1 = c1 * (*in) + c2 * yt1;
    *out = yt1;

    p->yt1 = yt1;
    return UT_OK;
}
