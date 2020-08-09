/*
 * Streson
 * 
 * This code has been extracted from the Csound opcode "streson".
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): John ffitch, Victor Lazzarini
 * Year: 1996, 1998
 * Location: Opcodes/repluck.c
 *
 */


#include <stdlib.h>
#include "utone.h"

int ut_streson_create(ut_streson **p) 
{
    *p = malloc(sizeof(ut_streson));
    return UT_OK;
}

int ut_streson_destroy(ut_streson **p) 
{
    ut_streson *pp = *p;
    ut_auxdata_free(&pp->buf);
    free(*p);
    return UT_OK;
}

int ut_streson_init(ut_data *ut, ut_streson *p) 
{
    int n;
    p->freq = 440.0;
    p->fdbgain = 0.8;
    p->size = (int) (ut->sr/20);   /* size of delay line */
    ut_auxdata_alloc(&p->buf, p->size * sizeof(UTFLOAT));
    p->Cdelay = (UTFLOAT*) p->buf.ptr; /* delay line */
    p->LPdelay = p->APdelay = 0.0; /* reset the All-pass and Low-pass delays */
    p->wpointer = p->rpointer = 0; /* reset the read/write pointers */
    for (n = 0; n < p->size; n++){
      p->Cdelay[n] = 0.0;
    }
    return UT_OK;
}

int ut_streson_compute(ut_data *ut, ut_streson *p, UTFLOAT *in, UTFLOAT *out) 
{
    UTFLOAT g = p->fdbgain;
    UTFLOAT freq;
    UTFLOAT a, s, w, sample, tdelay, fracdelay;
    int delay;
    int rp = p->rpointer, wp = p->wpointer;
    int size = p->size;
    UTFLOAT APdelay = p->APdelay;
    UTFLOAT LPdelay = p->LPdelay;
    int vdt;

    freq = p->freq;
    if (freq < 20.0) freq = 20.0;   /* lowest freq is 20 Hz */
    tdelay = ut->sr/freq;
    delay = (int) (tdelay - 0.5); /* comb delay */
    fracdelay = tdelay - (delay + 0.5); /* fractional delay */
    vdt = size - delay;       /* set the var delay */
    a = (1.0-fracdelay)/(1.0+fracdelay);   /* set the all-pass gain */
    
    UTFLOAT tmpo;
    rp = (vdt + wp);
    if (rp >= size) rp -= size;
    tmpo = p->Cdelay[rp];
    w = *in + tmpo;
    s = (LPdelay + w)*0.5;
    LPdelay = w;
    *out = sample = APdelay + s*a;
    APdelay = s - (sample*a);
    p->Cdelay[wp] = sample*g;
    wp++;
    if (wp == size) wp=0;
    p->rpointer = rp; p->wpointer = wp;
    p->LPdelay = LPdelay; p->APdelay = APdelay;
    return UT_OK;
}
