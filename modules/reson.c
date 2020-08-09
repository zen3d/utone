/* 
 * reson
 *
 * This code has been extracted from the Csound opcode "reson".
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): Barry Vercoe, John FFitch, Gabriel Maldonado
 * Year: 1991
 * Location: OOps/afilters.c
 *
 */

#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI		3.14159265358979323846	
#endif 

#include "utone.h"

int ut_reson_create(ut_reson **p)
{
    *p = malloc(sizeof(ut_reson));
    return UT_OK;
}

int ut_reson_destroy(ut_reson **p)
{
    free(*p);
    return UT_OK;
}

int ut_reson_init(ut_data *ut, ut_reson *p)
{
    p->scale = 0;
    p->freq = 4000;
    p->bw = 1000;
    p->prvfreq = p->prvbw = -100.0;
    p->tpidsr = (2.0 * M_PI) / ut->sr * 1.0;
    p->yt1 = p->yt2 = 0.0;
    return UT_OK;
}


int ut_reson_compute(ut_data *ut, ut_reson *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT c3p1, c3t4;
    UTFLOAT yt1, yt2, c1 = p->c1, c2 = p->c2, c3 = p->c3;
    int flag = 0;

    yt1 = p->yt1; 
    yt2 = p->yt2;
    
    UTFLOAT yt0;
    UTFLOAT cf = p->freq;
    
    /* bw needs to stay positive so it doesn't blow the filter up */
    UTFLOAT bw = fabs(p->bw);
    
    if (cf != p->prvfreq ) {
        p->prvfreq = cf;
        p->cosf = cos(cf * (p->tpidsr));
        flag = 1;
    }
    
    if (bw != p->prvbw) {
        p->prvbw = bw;
        c3 = p->c3 = exp(bw * (-1.0 * p->tpidsr));
        flag = 1;
    }
    
    if (flag) {
        c3p1 = c3 + 1.0;
        c3t4 = c3 * 4.0;
        c2 = p->c2 = c3t4 * p->cosf / c3p1;
        c1 = p->c1 = 1.0;
        flag = 0;
    }
    
    yt0 = c1 * *in  + c2 * yt1 - c3 * yt2;
    *out = yt0;
    yt2 = yt1;
    yt1 = yt0;
    p->yt1 = yt1; p->yt2 = yt2;
    return UT_OK;
}
