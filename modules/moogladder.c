/*
 * Moogladder
 *
 * This code has been extracted from the Csound opcode "Moogladder".
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): Victor Lazzarini
 * Year: 2001
 * Location: Opcodes/newfils.c
 */

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "utone.h"

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

#define UTFLOAT2LONG(x) lrintf(x)


/* John ffitch tanh function to speed up inner loop */ 

static double my_tanh(double x)
{
    /* use the fact that tanh(-x) = - tanh(x)
       and if x>~4 tanh is approx constant 1
       and for small x tanh(x) =~ x
       So giving a cheap approximation */
    int sign = 1;
    if (x<0) { 
        sign=-1; 
        x= -x;
    }
    if (x>=4.0) {
      return sign;
    }
    if (x<0.5) return x*sign;
    return sign*tanh(x);
}

int ut_moogladder_create(ut_moogladder **t){
    *t = malloc(sizeof(ut_moogladder));
    return UT_OK;
}

int ut_moogladder_destroy(ut_moogladder **t){
    free(*t);
    return UT_OK;
}

int ut_moogladder_init(ut_data *ut, ut_moogladder *p){
    p->istor = 0.0;
    p->res = 0.4;
    p->freq = 1000;
    int i;

    if (p->istor == 0.0) {
      for (i = 0; i < 6; i++)
        p->delay[i] = 0.0;
      for (i = 0; i < 3; i++)
        p->tanhstg[i] = 0.0;
      p->oldfreq = 0.0;
      p->oldres = -1.0;     /* ensure calculation on first cycle */
    }
    return UT_OK;
}

int ut_moogladder_compute(ut_data *ut, ut_moogladder *p, UTFLOAT *in, UTFLOAT *out){
    UTFLOAT freq = p->freq;
    UTFLOAT res = p->res;
    UTFLOAT res4;
    UTFLOAT *delay = p->delay;
    UTFLOAT *tanhstg = p->tanhstg;
    UTFLOAT stg[4], input;
    UTFLOAT acr, tune;
#define THERMAL (0.000025) /* (1.0 / 40000.0) transistor thermal voltage  */
    int     j, k;

    if (res < 0) res = 0;

    if (p->oldfreq != freq || p->oldres != res) {
        UTFLOAT f, fc, fc2, fc3, fcr;
        p->oldfreq = freq;
        /* sr is half the actual filter sampling rate  */
        fc =  (UTFLOAT)(freq/ut->sr);
        f  =  0.5*fc;
        fc2 = fc*fc;
        fc3 = fc2*fc;
        /* frequency & amplitude correction  */
        fcr = 1.8730*fc3 + 0.4955*fc2 - 0.6490*fc + 0.9988;
        acr = -3.9364*fc2 + 1.8409*fc + 0.9968;
        tune = (1.0 - exp(-((2 * M_PI)*f*fcr))) / THERMAL;   /* filter tuning  */
        p->oldres = res;
        p->oldacr = acr;
        p->oldtune = tune;
    } else {
        res = p->oldres;
        acr = p->oldacr;
        tune = p->oldtune;
    }
    res4 = 4.0*(UTFLOAT)res*acr;

    /* oversampling  */
    for (j = 0; j < 2; j++) {
        /* filter stages  */
        input = *in - res4 /*4.0*res*acr*/ *delay[5];
        delay[0] = stg[0] = delay[0] + tune*(my_tanh(input*THERMAL) - tanhstg[0]);
        for (k = 1; k < 4; k++) {
          input = stg[k-1];
          stg[k] = delay[k]
            + tune*((tanhstg[k-1] = my_tanh(input*THERMAL))
                    - (k != 3 ? tanhstg[k] : my_tanh(delay[k]*THERMAL)));
          delay[k] = stg[k];
        }
        /* 1/2-sample delay for phase compensation  */
        delay[5] = (stg[3] + delay[4])*0.5;
        delay[4] = stg[3];
    }
    *out = (UTFLOAT) delay[5];
    return UT_OK;
}
