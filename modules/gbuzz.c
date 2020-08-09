/*
 * GBuzz
 * 
 * This code has been extracted from the Csound opcode "gbuzz".
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): Gabriel Maldonado
 * Year: 1991
 * Location: ugens/ugens4.c
 *
 */
#include <math.h>
#include <stdlib.h>
#include "utone.h"

/* Binary positive power function */
static UTFLOAT intpow1(UTFLOAT x, int32_t n)   
{
    UTFLOAT ans = 1.0;
    while (n!=0) {
      if (n&1) ans = ans * x;
      n >>= 1;
      x = x*x;
    }
    return ans;
}


int ut_gbuzz_create(ut_gbuzz **p)
{
    *p = malloc(sizeof(ut_gbuzz));
    return UT_OK;
}

int ut_gbuzz_destroy(ut_gbuzz **p)
{
    free(*p);
    return UT_OK;
}

int ut_gbuzz_init(ut_data *ut, ut_gbuzz *p, ut_ftbl *ft, UTFLOAT iphs)
{
    p->freq = 440;
    p->amp = 0.4;
    p->nharm = 4;
    p->lharm = 1;
    p->mul = 0.1;
    p->ft = ft;
    p->iphs = iphs; 
    
    if (p->iphs >= 0) {
        p->lphs = (int32_t)(p->iphs * UT_FT_MAXLEN);
        p->prvr = 0.0;
    }
    p->last = 1.0;
    return UT_OK;
}

int ut_gbuzz_compute(ut_data *ut, ut_gbuzz *p, UTFLOAT *in, UTFLOAT *out)
{
    ut_ftbl *ftp;
    UTFLOAT *ftbl;
    int32_t phs, inc, lobits, lenmask, k, km1, kpn, kpnm1;
    UTFLOAT r, absr, num, denom, scal, last = p->last;
    int32_t nn, lphs = p->lphs;
    
    ftp = p->ft;
    ftbl = ftp->tbl;
    lobits = ftp->lobits;
    lenmask = (int32_t) ftp->size - 1;
    k = (int32_t)p->lharm;
    
    if ((nn = (int32_t)p->nharm)<0) nn = -nn;
    
    if (nn == 0) {
        nn = 1;
    }
    km1 = k - 1;
    kpn = k + nn;
    kpnm1 = kpn - 1;
    
    if ((r = p->mul) != p->prvr || nn != p->prvn) {
        p->twor = r + r;
        p->rsqp1 = r * r + 1.0;
        p->rtn = intpow1(r, nn);
        p->rtnp1 = p->rtn * r;
        
        if ((absr = fabs(r)) > 0.999 && absr < 1.001) {
            p->rsumr = 1.0 / nn;
        } else {
            p->rsumr = (1.0 - absr) / (1.0 - fabs(p->rtn));
        }
        
        p->prvr = r;
        p->prvn = (int16_t)nn;
    }
    
    scal =  p->amp * p->rsumr;
    inc = (int32_t)(p->freq * ftp->sicvt);
    phs = lphs >>lobits;
    denom = p->rsqp1 - p->twor * ftbl[phs];
    num = ftbl[phs * k & lenmask]
        - r * ftbl[phs * km1 & lenmask]
        - p->rtn * ftbl[phs * kpn & lenmask]
        + p->rtnp1 * ftbl[phs * kpnm1 & lenmask];
    
    if (denom > 0.0002 || denom < -0.0002) {
        *out = last = num / denom * scal;
    } else if (last<0) {
        *out = last = - *out;
    } else {
        *out = last = *out;
    }
    
    lphs += inc;
    lphs &= UT_FT_PHMASK;
    p->last = last;
    p->lphs = lphs;
    return UT_OK;
}
