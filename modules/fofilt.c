/*
 * Fofilt
 *
 * This code has been extracted from the Csound opcode "fofilter".
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): Victor Lazzarini
 * Year: 2004
 * Location: Opcodes/newfils.c
 *
 */

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "utone.h"

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif


int ut_fofilt_create(ut_fofilt **p)
{
    *p = malloc(sizeof(ut_fofilt));
    return UT_OK;
}

int ut_fofilt_destroy(ut_fofilt **p)
{
    free(*p);
    return UT_OK;
}

int ut_fofilt_init(ut_data *ut, ut_fofilt *p)
{
   p->tpidsr = 2.0*M_PI / ut->sr;
   p->sr = ut->sr;

   p->freq = 1000;
   p->atk = 0.007;
   p->dec = 0.04;
   p->istor = 0.0;

   int i;
   if (p->istor==0.0){
        for (i=0; i<4; i++)
         p->delay[i] = 0.0;
   }
   return UT_OK;
}

int ut_fofilt_compute(ut_data *ut, ut_fofilt *p, UTFLOAT *in, UTFLOAT *out)
{

    UTFLOAT freq = p->freq;
    UTFLOAT ris = p->atk;
    UTFLOAT dec = p->dec;
    UTFLOAT *delay = p->delay,ang=0,fsc,rrad1=0,rrad2=0;
    UTFLOAT w1,y1,w2,y2;
    UTFLOAT lfrq = -1.0, lrs = -1.0, ldc = -1.0;

    UTFLOAT frq = freq;
    UTFLOAT rs = ris;
    UTFLOAT dc = dec;
    if (frq != lfrq || rs != lrs || dc != ldc) {
        lfrq = frq; lrs = rs; ldc = dc;
        ang = (UTFLOAT)p->tpidsr*frq;
        fsc = sin(ang) - 3.0;

        rrad1 =  pow(10.0, fsc/(dc*ut->sr));
        rrad2 =  pow(10.0, fsc/(rs*ut->sr));
    }

    w1  = *in + 2.0*rrad1*cos(ang)*delay[0] - rrad1*rrad1*delay[1];
    y1 =  w1 - delay[1];
    delay[1] = delay[0];
    delay[0] = w1;

    w2  = *in + 2.0*rrad2*cos(ang)*delay[2] - rrad2*rrad2*delay[3];
    y2 =  w2 - delay[3];
    delay[3] = delay[2];
    delay[2] = w2;

    *out = (UTFLOAT) (y1 - y2);

    return UT_OK;
}
