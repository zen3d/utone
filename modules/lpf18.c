/*
 * LPF18 
 * 
 * This code has been extracted from the Csound opcode "lpf18".
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): John ffitch, Josep Comajuncosas 
 * Year: 2000
 * Location: Opcodes/pitch.c
 *
 */

#include <math.h>
#include <stdlib.h>
#include "utone.h"

int ut_lpf18_create(ut_lpf18 **p)
{
    *p = malloc(sizeof(ut_lpf18));
    return UT_OK;
}

int ut_lpf18_destroy(ut_lpf18 **p)
{
    free(*p);
    return UT_OK;
}

int ut_lpf18_init(ut_data *ut, ut_lpf18 *p)
{
    p->cutoff = 1000;
    p->res = 0.8;
    p->dist = 2;

    p->ay1 = 0.0;
    p->ay2 = 0.0;
    p->aout = 0.0;
    p->lastin = 0.0;
    p->onedsr = 1.0 / ut->sr;
    return UT_OK;
}

int ut_lpf18_compute(ut_data *ut, ut_lpf18 *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT ay1 = p->ay1;
    UTFLOAT ay2 = p->ay2;
    UTFLOAT aout = p->aout;
    UTFLOAT lastin = p->lastin;
    double value = 0.0;
    int   flag = 1;
    UTFLOAT lfc=0, lrs=0, kres=0, kfcn=0, kp=0, kp1=0,  kp1h=0;
    double lds = 0.0;

    UTFLOAT fco, res, dist;
    UTFLOAT ax1  = lastin;
    UTFLOAT ay11 = ay1;
    UTFLOAT ay31 = ay2;
    fco = p->cutoff;
    res = p->res;
    dist = p->dist;

    if (fco != lfc || flag) {
        lfc = fco;
        kfcn = 2.0 * fco * p->onedsr;
        kp = ((-2.7528 * kfcn + 3.0429) * kfcn +
                1.718) * kfcn - 0.9984;
        kp1 = kp + 1.0;
        kp1h = 0.5 * kp1;
        flag = 1;
    }

    if (res != lrs || flag) {
        lrs = res;
        kres = res * (((-2.7079 * kp1 + 10.963) * kp1
                           - 14.934) * kp1 + 8.4974);
        flag = 1;
    }

    if (dist != lds || flag) {
        lds = dist;
        value = 1.0 + (dist * (1.5 + 2.0 * res * (1.0 - kfcn)));
    }

    flag = 0;
    lastin = *in - tanh(kres*aout);
    ay1 = kp1h * (lastin + ax1) - kp * ay1;
    ay2 = kp1h * (ay1 + ay11) - kp * ay2;
    aout = kp1h * (ay2 + ay31) - kp * aout;

    *out = tanh(aout * value);

    p->ay1 = ay1;
    p->ay2 = ay2;
    p->aout = aout;
    p->lastin = lastin;
    return UT_OK;
}
