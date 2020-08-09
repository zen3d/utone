/*
 * pluck
 * 
 * This code has been extracted from the Csound opcode "pluck"
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): Barry Vercoe, John ffitch
 * Year: 1991
 * Location: OOps/ugens4.c
 *
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utone.h"

#define PLUKMIN 64
 
int ut_pluck_create(ut_pluck **p)
{
    *p = malloc(sizeof(ut_pluck));
    return UT_OK;
}

int ut_pluck_destroy(ut_pluck **p)
{
    ut_pluck *pp = *p;
    ut_auxdata_free(&pp->auxch);
    free(*p);
    return UT_OK;
}

static void ut_pluck_reinit(ut_data *ut, ut_pluck *p)
{
    int n;
    UTFLOAT val = 0;
    UTFLOAT *ap = (UTFLOAT *)p->auxch.ptr;
    for (n=p->npts; n--; ) {   
        val = (UTFLOAT) ((UTFLOAT) ut_rand(ut) / UT_RANDMAX);
        *ap++ = (val * 2) - 1;
    }
    p->phs256 = 0;
}

int ut_pluck_init(ut_data *ut, ut_pluck *p, UTFLOAT ifreq)
{
    int32_t npts;

    p->amp = 0.5;
    p->ifreq = ifreq;
    p->freq = ifreq;

    if ((npts = (int32_t)(ut->sr / p->ifreq)) < PLUKMIN) {
        npts = PLUKMIN;                  
    }
    
    ut_auxdata_alloc(&p->auxch, (npts + 1) * sizeof(UTFLOAT));
    p->maxpts = npts;
    p->npts = npts;

    ut_pluck_reinit(ut, p);
    /* tuned pitch convt */
    p->sicps = (npts * 256.0 + 128.0) * (1.0 / ut->sr);
    p->init = 1;
    return UT_OK;
}

int ut_pluck_compute(ut_data *ut, ut_pluck *p, UTFLOAT *trig, UTFLOAT *out)
{
    UTFLOAT *fp;
    int32_t phs256, phsinc, ltwopi, offset;
    UTFLOAT frac, diff;


    if(*trig != 0) {
        p->init = 0;
        ut_pluck_reinit(ut, p);
    }

    if(p->init) {
        *out = 0;
        return UT_OK;
    }

    phsinc = (int32_t)(p->freq * p->sicps);
    phs256 = p->phs256;
    ltwopi = p->npts << 8;
    offset = phs256 >> 8;
    fp = (UTFLOAT *)p->auxch.ptr + offset;     /* lookup position   */
    diff = fp[1] - fp[0];
    frac = (UTFLOAT)(phs256 & 255) / 256.0; /*  w. interpolation */
    *out = (fp[0] + diff*frac) * p->amp; /*  gives output val */
    if ((phs256 += phsinc) >= ltwopi) {
        int nn;
        UTFLOAT preval;
        phs256 -= ltwopi;               
        fp=(UTFLOAT *)p->auxch.ptr;
        preval = fp[0];                
        fp[0] = fp[p->npts];
        fp++;
        nn = p->npts;
        do {          
            /* 1st order recursive filter*/
            preval = (*fp + preval) * 0.5;
            *fp++ = preval;
        } while (--nn);
    }
    p->phs256 = phs256;
    return UT_OK;
}
