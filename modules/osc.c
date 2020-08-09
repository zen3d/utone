/*
 * Osc
 *
 * This code has been extracted from the Csound opcode "oscili".
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): Barry Vercoe, John FFitch, Robin Whittle
 * Year: 1991
 * Location: OOps/ugens2.c
 *
 */

#include <stdlib.h>
#include <math.h>
#include "utone.h"

int ut_osc_create(ut_osc **osc)
{
    *osc = malloc(sizeof(ut_osc));
    return UT_OK;
}

int ut_osc_destroy(ut_osc **osc)
{
    free(*osc);
    return UT_NOT_OK;
}

int ut_osc_init(ut_data *ut, ut_osc *osc, ut_ftbl *ft, UTFLOAT iphs)
{
    osc->freq = 440.0;
    osc->amp = 0.2;
    osc->tbl = ft;
    osc->iphs = fabs(iphs);
    osc->inc = 0;
    if (osc->iphs >= 0){
        osc->lphs = ((int32_t)(osc->iphs * UT_FT_MAXLEN)) & UT_FT_PHMASK;
    }

    return UT_OK;
}

int ut_osc_compute(ut_data *ut, ut_osc *osc, UTFLOAT *in, UTFLOAT *out)
{
    ut_ftbl *ftp;
    UTFLOAT amp, cps, fract, v1, v2, *ft;
    int32_t phs, lobits;
    int32_t pos;
    UTFLOAT sicvt = osc->tbl->sicvt;

    ftp = osc->tbl;
    lobits = osc->tbl->lobits;
    amp = osc->amp;
    cps = osc->freq;
    phs = osc->lphs;
    ft = osc->tbl->tbl;
    
    osc->inc = (int32_t)lrintf(cps * sicvt);

    fract = ((phs) & ftp->lomask) * ftp->lodiv;
    pos = phs>>lobits;
    v1 = *(ft + pos);
    v2 = *(ft + ((pos + 1) % ftp->size));
    *out = (v1 + (v2 - v1) * fract) * amp;
    phs += osc->inc;
    phs &= UT_FT_PHMASK;

    osc->lphs = phs;
    return UT_OK;
}
