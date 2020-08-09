#include <stdlib.h>
#include <math.h>
#include "utone.h"

int ut_oscmorph_create(ut_oscmorph **p)
{
    *p = malloc(sizeof(ut_oscmorph));
    return UT_OK;
}

int ut_oscmorph_destroy(ut_oscmorph **p)
{
    free(*p);
    return UT_OK;
}

int ut_oscmorph_init(ut_data *ut, ut_oscmorph *osc, ut_ftbl **ft, int nft, UTFLOAT iphs)
{
    int i;
    osc->freq = 440.0;
    osc->amp = 0.2;
    osc->tbl = ft;
    osc->iphs = fabs(iphs);
    osc->inc = 0;
    osc->lphs = ((int32_t)(osc->iphs * UT_FT_MAXLEN)) & UT_FT_PHMASK;
    osc->wtpos = 0.0;
    osc->nft = nft;
    uint32_t prev = (uint32_t)ft[0]->size;
    for(i = 0; i < nft; i++) {
        if(prev != ft[i]->size) {
            fprintf(stderr, "ut_oscmorph: size mismatch\n");
            return UT_NOT_OK;
        }
        prev = (uint32_t)ft[i]->size;
    }
    return UT_OK;
}

int ut_oscmorph_compute(ut_data *ut, ut_oscmorph *osc, UTFLOAT *in, UTFLOAT *out)
{
    ut_ftbl *ftp1;
    UTFLOAT amp, cps, fract, v1, v2;
    UTFLOAT *ft1, *ft2;
    int32_t phs, lobits, pos;
    UTFLOAT sicvt = osc->tbl[0]->sicvt;

    /* Use only the fractional part of the position or 1 */
    if (osc->wtpos > 1.0) {
        osc->wtpos -= (int)osc->wtpos;
    }
    UTFLOAT findex = osc->wtpos * (osc->nft - 1);
    int index = floor(findex);
    UTFLOAT wtfrac = findex - index;

    lobits = osc->tbl[0]->lobits;
    amp = osc->amp;
    cps = osc->freq;
    phs = osc->lphs;
    ftp1 = osc->tbl[index];
    ft1 = osc->tbl[index]->tbl;

    if(index >= osc->nft - 1) {
        ft2 = ft1;
    } else {
        ft2 = osc->tbl[index + 1]->tbl;
    }
    
    osc->inc = (int32_t)lrintf(cps * sicvt);

    fract = ((phs) & ftp1->lomask) * ftp1->lodiv;

    pos = phs >> lobits;

    v1 = (1 - wtfrac) * 
        *(ft1 + pos) + 
        wtfrac * 
        *(ft2 + pos);
    v2 = (1 - wtfrac) * 
        *(ft1 + ((pos + 1) % ftp1->size))+ 
        wtfrac * 
        *(ft2 + ((pos + 1) % ftp1->size));

    *out = (v1 + (v2 - v1) * fract) * amp;

    phs += osc->inc;
    phs &= UT_FT_PHMASK;

    osc->lphs = phs;
    return UT_OK;
}
