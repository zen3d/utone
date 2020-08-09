#include <math.h>
#include "utone.h"
#include "kiss_fftr.h"

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

int ut_gen_scrambler(ut_data *ut, ut_ftbl *src, ut_ftbl **dest)
{

    uint32_t size = (src->size % 2 == 0) ? src->size : src->size - 1;
    ut_ftbl *dst;
    ut_ftbl_create(ut, &dst, size);
    kiss_fftr_cfg fft, ifft;
    kiss_fft_cpx *tmp;

    /* set up kissfft */
    fft = kiss_fftr_alloc(size, 0, NULL, NULL);
    ifft = kiss_fftr_alloc(size, 1, NULL, NULL);
    tmp = malloc(sizeof(kiss_fft_cpx) * size);
    memset(tmp, 0, sizeof(UTFLOAT) * size);
    kiss_fftr(fft, src->tbl, tmp);

    uint32_t i;
    UTFLOAT mag, phs;
    for(i = 0; i < size / 2; i++) {
        mag = sqrt(tmp[i].r * tmp[i].r + tmp[i].i * tmp[i].i) / size;
        phs = ((UTFLOAT)ut_rand(ut) / UT_RANDMAX) * 2 * M_PI;
        tmp[i].r = mag * cos(phs);
        tmp[i].i = mag * sin(phs);
    }

    tmp[0].r = 0;
    tmp[0].i = 0;
    tmp[size / 2 - 1].r = 0;
    tmp[size / 2 - 1].i = 0;

    kiss_fftri(ifft, tmp, dst->tbl);
    UTFLOAT max = -1;
    UTFLOAT val = 0;
    for(i = 0; i < size; i++) {
        val = fabs(dst->tbl[i]); 
        if(val > max) {
            max = val;
        }
    }

    for(i = 0; i < size; i++) {
       dst->tbl[i] /= max;
    }

    kiss_fftr_free(fft);
    kiss_fftr_free(ifft);
    KISS_FFT_FREE(tmp);
    
    *dest = dst;
    return UT_OK;
}
