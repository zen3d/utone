/*
 * posc3
 * 
 * This code has been extracted from the Csound opcode "poscil3".
 * It has been modified to work as a Soundpipe module.
 * 
 * Original Author(s): Gabriel Maldonado, John ffitch
 * Year: 1998
 * Location: Opcodes/uggab.c
 *
 */

#include <stdlib.h>
#include <math.h>
#include "utone.h"
int ut_posc3_create(ut_posc3 **posc3)
{
    *posc3 = malloc(sizeof(ut_posc3));
    return UT_OK;
}

int ut_posc3_destroy(ut_posc3 **posc3)
{
    free(*posc3);
    return UT_NOT_OK;
}

int ut_posc3_init(ut_data *ut, ut_posc3 *posc3, ut_ftbl *ft)
{

    posc3->amp = 0.2;
    posc3->freq = 440.0;
    posc3->iphs = 0.0;
    posc3->onedsr = 1.0 / ut->sr;

    posc3->tbl = ft;
    posc3->tablen = (int32_t) ft->size;
    posc3->tablenUPsr = posc3->tablen * posc3->onedsr;
    posc3->phs = posc3->iphs * posc3->tablen;
    return UT_OK;
}

int ut_posc3_compute(ut_data *ut, ut_posc3 *posc3, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT *ftab;
    UTFLOAT fract;
    UTFLOAT phs  = posc3->phs;
    UTFLOAT si   = posc3->freq * posc3->tablen * posc3->onedsr;
    UTFLOAT amp = posc3->amp;
    int x0;
    UTFLOAT y0, y1, ym1, y2;

    ftab = posc3->tbl->tbl;

    x0    = (int32_t )phs;
    fract = (UTFLOAT)(phs - (UTFLOAT)x0);
    x0--;

    if (x0<0) {
        ym1 = ftab[posc3->tablen-1]; x0 = 0;
    }
    else ym1 = ftab[x0++];
    y0    = ftab[x0++];
    y1    = ftab[x0++];
    if (x0>posc3->tablen) y2 = ftab[1];
    else y2 = ftab[x0];
    {
        UTFLOAT frsq = fract*fract;
        UTFLOAT frcu = frsq*ym1;
        UTFLOAT t1   = y2 + y0+y0+y0;
        *out     = amp * (y0 + 0.5 *frcu +
        fract*(y1 - frcu/6.0 - t1/6.0
        - ym1/3.0) +
        frsq*fract*(t1/6.0 - 0.5*y1) +
        frsq*(0.5* y1 - y0));
    }
    phs += si;
    while (phs >= posc3->tablen) {
        phs -= posc3->tablen;
    }
    while (phs < 0.0) {
        phs += posc3->tablen;
        posc3->phs = phs;
    }
    posc3->phs = phs;
    return UT_OK;
}
