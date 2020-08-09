/*
 * Fosc
 *
 * This code has been extracted from the Csound opcode "foscili".
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): Barry Vercoe, John ffitch
 * Year: 1991
 * Location: OOps/ugens3.c
 *
 */

#include <stdlib.h>
#include "utone.h"

int ut_fosc_create(ut_fosc **p)
{
    *p = malloc(sizeof(ut_fosc));
    return UT_OK;
}

int ut_fosc_destroy(ut_fosc **p)
{
    free(*p);
    return UT_OK;
}

int ut_fosc_init(ut_data *ut, ut_fosc *p, ut_ftbl *ft)
{
    p->freq = 440;
    p->amp = 0.4;
    p->iphs = 0.0;
    p->ft = ft;

    p->mod = 1.0;
    p->car = 1.0;
    p->indx = 1.0;

    p->cphs = p->mphs = (int32_t)(p->iphs * UT_FT_MAXLEN);

    return UT_OK;
}

int ut_fosc_compute(ut_data *ut, ut_fosc *p, UTFLOAT *in, UTFLOAT *out)
{

    ut_ftbl *ftp;

    UTFLOAT  amp, cps, fract, v1, v2, car, fmod, cfreq, mod;
    UTFLOAT  xcar, xmod, ndx, *ftab;
    int32_t  mphs, cphs, minc, cinc, lobits;
    UTFLOAT  sicvt = p->ft->sicvt;
    UTFLOAT  *ft;

    ftp = p->ft;
    ft = ftp->tbl;
    lobits = ftp->lobits;
    mphs = p->mphs;
    cphs = p->cphs;
    cps  = p->freq;
    amp  = p->amp;
    xcar = p->car;
    xmod = p->mod;

    car = cps * xcar;
    mod = cps * xmod;
    ndx = p->indx * mod;
    minc = (int32_t)(mod * sicvt);
    mphs &= UT_FT_PHMASK;
    fract = ((mphs) & ftp->lomask) * ftp->lodiv;
    ftab = ft + (mphs >> lobits);
    v1 = ftab[0];

    if(ftab[0] == p->ft->tbl[p->ft->size - 1]) {
        v2 = p->ft->tbl[0];
    } else {
        v2 = ftab[1];
    }

    fmod = (v1 + (v2 - v1) * fract) * ndx;
    mphs += minc;
    cfreq = car + fmod;
    cinc = (int32_t)(cfreq * sicvt);
    cphs &= UT_FT_PHMASK;
    fract = ((cphs) & ftp->lomask) * ftp->lodiv;
    ftab = ft + (cphs >>lobits);
    v1 = ftab[0];

    if(ftab[0] == p->ft->tbl[p->ft->size - 1]) {
        v2 = p->ft->tbl[0];
    } else {
        v2 = ftab[1];
    }

    *out = (v1 + (v2 - v1) * fract) * amp;
    cphs += cinc;
    p->mphs = mphs;
    p->cphs = cphs;

    return UT_OK;
}
