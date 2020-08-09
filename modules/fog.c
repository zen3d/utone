/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include <math.h>
#include "utone.h"


#define PFRAC1(x)   ((UTFLOAT)((x) & ftp1->lomask) * ftp1->lodiv)

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

#define MPIDSR -M_PI/ut->sr

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

static UTFLOAT intpow(UTFLOAT x, int32_t n)
{
    if (n<0) {
      n = -n;
      x = 1.0/x;
    }
    return intpow1(x, n);
}

static int newpulse(ut_data *ut, ut_fog *p, ut_fog_overlap *ovp, UTFLOAT amp,
                    UTFLOAT fund, UTFLOAT ptch)
{
    UTFLOAT octamp = amp, oct;
    UTFLOAT form = ptch / p->ftp1->sicvt, fogcvt = p->fogcvt;
    int32_t rismps, newexp = 0;
    ovp->timrem = (int32_t)(p->dur * ut->sr);

    if ((oct = p->oct) > 0.0) {
        int32_t ioct = (int32_t)oct, bitpat = ~(-1L << ioct);
        if (bitpat & ++p->fofcount) return(0);
        if ((bitpat += 1) & p->fofcount) octamp *= (1.0) + ioct - oct;
    }

    if (fund == 0.0) ovp->formphs = 0;
    else ovp->formphs = (int32_t)(p->fundphs * form / fund) & UT_FT_PHMASK;

    ovp->forminc = (int32_t)(ptch * fogcvt);

    if (p->band != p->prvband) {
        p->prvband = p->band;
        p->expamp = exp(p->band * MPIDSR);
        newexp = 1;
    }

    if (p->ris >= (1.0 / ut->sr)  && form != 0.0) {
        ovp->risphs = (uint32_t)(ovp->formphs / (fabs(form))
                                    / p->ris);
        ovp->risinc = (int32_t)(p->ftp1->sicvt / p->ris);
        rismps = UT_FT_MAXLEN / ovp->risinc;
    } else {
        ovp->risphs = UT_FT_MAXLEN;
        rismps = 0;
    }
    ovp->formphs = (ovp->formphs + p->spdphs) & UT_FT_PHMASK;

    if (newexp || rismps != p->prvsmps) {
        if ((p->prvsmps = rismps)) p->preamp = intpow(p->expamp, -rismps);
        else p->preamp = 1.0;
    }

    ovp->curamp = octamp * p->preamp;
    ovp->expamp = p->expamp;

    if ((ovp->dectim = (int32_t)(p->dec * ut->sr )) > 0) {
        ovp->decinc = (int32_t)(p->ftp1->sicvt / p->dec);
    }

    ovp->decphs = UT_FT_PHMASK;

    ovp->pos = p->spd * p->ftp1->size;
    ovp->inc = p->trans;

    return 1;
}

int ut_fog_create(ut_fog **p)
{
    *p = malloc(sizeof(ut_fog));
    return UT_OK;
}

int ut_fog_destroy(ut_fog **p)
{
    ut_fog *pp = *p;
    ut_auxdata_free(&pp->auxch);
    free(*p);
    return UT_OK;
}

int ut_fog_init(ut_data *ut, ut_fog *p, ut_ftbl *wav, ut_ftbl *win, int iolaps, UTFLOAT iphs)
{
    p->amp = 0.5;
    p->dens = 80;
    p->trans = 1;
    p->spd = 0;
    p->oct = 0;
    p->band = 50;
    p->ris = 0.01;
    p->dec = 0.07;
    p->dur = 0.1;
    p->iolaps = iolaps;
    p->iphs = iphs;
    p->ftp1 = wav;
    p->ftp2 = win;

    ut_fog_overlap *ovp, *nxtovp;
    int32_t olaps;
    p->fogcvt = UT_FT_MAXLEN/(p->ftp1)->size;
    p->spdphs = 0L;
    if (p->iphs == 0.0) p->fundphs = UT_FT_MAXLEN;
    else p->fundphs = (int32_t)(p->iphs * UT_FT_MAXLEN) & UT_FT_PHMASK;

    olaps = (int32_t)p->iolaps;

    ut_auxdata_alloc(&p->auxch, (size_t)olaps * sizeof(ut_fog_overlap));
    ovp = &p->basovrlap;
    nxtovp = (ut_fog_overlap *) p->auxch.ptr;

    do {
        ovp->nxtact = NULL;
        ovp->nxtfree = nxtovp;
        ovp = nxtovp++;
    } while (--olaps);

    ovp->nxtact  = NULL;
    ovp->nxtfree = NULL;
    p->fofcount = -1;
    p->prvband = 0.0;
    p->expamp = 1.0;
    p->prvsmps = 0;
    p->preamp = 1.0;
    p->fmtmod  = 0;
    return UT_OK;
}

int ut_fog_compute(ut_data *ut, ut_fog *p, UTFLOAT *in, UTFLOAT *out)
{
    ut_fog_overlap *ovp;
    ut_ftbl *ftp1,  *ftp2;
    UTFLOAT  amp, fund, ptch, speed;
    UTFLOAT fract;
    int32_t fund_inc;
    int32_t incr;

    int32_t ndx;
    UTFLOAT x1, x2;


    amp = p->amp;
    fund = p->dens;
    ptch = p->trans;
    speed = p->spd;
    ftp1 = p->ftp1;
    ftp2 = p->ftp2;
    fund_inc = (int32_t)(fund * ftp1->sicvt);

    if (p->fundphs & UT_FT_MAXLEN) {
        p->fundphs &= UT_FT_PHMASK;
        ovp = p->basovrlap.nxtfree;
        if (newpulse(ut, p, ovp, amp, fund, ptch)) {
            ovp->nxtact = p->basovrlap.nxtact;
            p->basovrlap.nxtact = ovp;
            p->basovrlap.nxtfree = ovp->nxtfree;
        }
    }
    *out = 0.0;
    ovp = &p->basovrlap;
    while (ovp->nxtact != NULL) {
        UTFLOAT result;
        ut_fog_overlap *prvact = ovp;
        ovp = ovp->nxtact;
        ndx = floor(ovp->pos);
        fract = ovp->pos - ndx;

        while(ndx >= ftp1->size) {
            ndx -= ftp1->size;
        }

        while(ndx < 0) ndx += ftp1->size;

        x1 = ftp1->tbl[ndx];
        x2 = ftp1->tbl[ndx + 1];

        result = x1 + (x2 - x1) * fract;

        ovp->pos += ovp->inc;

        if (ovp->risphs < UT_FT_MAXLEN) {
            /* bounds checking so it doesn't segfault */
            incr = (ovp->risphs >> ftp2->lobits);
            if(incr <= ftp2->size) {
                result *= *(ftp2->tbl + incr );
            } else {
                result = 0;
            }
            ovp->risphs += ovp->risinc;
        }
        if (ovp->timrem <= ovp->dectim) {
            incr = (ovp->decphs >> ftp2->lobits);
            if(incr <= ftp2->size) {
                result *= *(ftp2->tbl + incr );
            } else {
                result = 0;
            }
            if ((ovp->decphs -= ovp->decinc) < 0)
            ovp->decphs = 0;
        }
        *out += (result * ovp->curamp);
        if (--ovp->timrem) ovp->curamp *= ovp->expamp;
        else {
            prvact->nxtact = ovp->nxtact;
            ovp->nxtfree = p->basovrlap.nxtfree;
            p->basovrlap.nxtfree = ovp;
            ovp = prvact;
        }
    }

    p->fundphs += fund_inc;
    p->spdphs = (int32_t)(speed * UT_FT_MAXLEN);
    p->spdphs &= UT_FT_PHMASK;
    return UT_OK;
}
