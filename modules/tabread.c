/*
 * Tabread
 *
 * This code has been extracted from the Csound opcode "tablei".
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author: Victor Lazzarini
 * Year: 2013
 * Location: OOps/ugtabs.c
 *
 */
#include <stdlib.h>
#include "math.h"
#include "utone.h"

int ut_tabread_create(ut_tabread **p)
{
    *p = malloc(sizeof(ut_tabread));
    return UT_OK;
}

int ut_tabread_destroy(ut_tabread **p)
{
    free(*p);
    return UT_OK;
}

int ut_tabread_init(ut_data *ut, ut_tabread *p, ut_ftbl *ft, int mode)
{
    p->ft = ft;
    p->mode = (UTFLOAT) mode;
    p->offset = 0;
    p->wrap = 0;
    return UT_OK;
}

int ut_tabread_compute(ut_data *ut, ut_tabread *p, UTFLOAT *in, UTFLOAT *out)
{
    int ndx, len = (int)p->ft->size;
    int32_t mask = (int)p->ft->size - 1;
    UTFLOAT index = p->index;
    UTFLOAT *tbl = p->ft->tbl;
    UTFLOAT offset = p->offset;
    UTFLOAT mul = 1, tmp, frac;

    if (p->mode) {
        mul = p->ft->size;
    }else {
        p->mul = 1;
    }

    int32_t iwrap = (int32_t)p->wrap;

    UTFLOAT x1, x2;
    tmp = (index + offset) * mul;
    ndx = floor(tmp);
    frac = tmp - ndx;
    if (iwrap) {
        if ((mask ? 0 : 1)) {
            while(ndx >= len) ndx -= len;
            while(ndx < 0)  ndx += len;
        }
        else ndx &= mask;
    } else {
        if (ndx >= len) ndx = len - 1;
        else if (ndx < 0) ndx = 0;
    }

    x1 = tbl[ndx];
    x2 = tbl[ndx+1];
    *out = x1 + (x2 - x1) * frac;
    return UT_OK;
}
