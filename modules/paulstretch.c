/*
 * PaulStretch
 * 
 * An implementation of the PaulStretch algorithm by Paul Nasca Octavian.
 * This code is based off the Python Numpy/Scipy implementation of 
 * PaulStretch, found here: https://github.com/paulnasca/paulstretch_python
 * 
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utone.h"
#include "kiss_fftr.h"

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

static void compute_block(ut_data *ut, ut_paulstretch *p) {
    uint32_t istart_pos = floor(p->start_pos);
    uint32_t pos; 
    uint32_t i;
    uint32_t windowsize = p->windowsize;
    uint32_t half_windowsize = p->half_windowsize;
    UTFLOAT *buf = p->buf;
    UTFLOAT *hinv_buf = p->hinv_buf;
    UTFLOAT *old_windowed_buf= p->old_windowed_buf;
    UTFLOAT *tbl = p->ft->tbl;
    UTFLOAT *window = p->window;
    UTFLOAT *output= p->output;
    for(i = 0; i < windowsize; i++) {
        /* Loop through buffer */
        pos = (istart_pos + i) % p->ft->size;

        if(p->wrap) {
            pos %= p->ft->size;
        } 

        if(pos < p->ft->size) {
            buf[i] = tbl[pos] * window[i];
        } else {
            buf[i] = 0;
        }
    }
    kiss_fftr(p->fft, buf, p->tmp1);
    for(i = 0; i < windowsize / 2; i++) {
        UTFLOAT mag = sqrt(p->tmp1[i].r*p->tmp1[i].r + p->tmp1[i].i*p->tmp1[i].i);
        UTFLOAT ph = ((UTFLOAT)ut_rand(ut) / UT_RANDMAX) * 2 * M_PI;
        p->tmp1[i].r = mag * cos(ph); 
        p->tmp1[i].i = mag * sin(ph); 
    }
    kiss_fftri(p->ifft, p->tmp1, buf);
    for(i = 0; i < windowsize; i++) {
        buf[i] *= window[i];
        if(i < half_windowsize) {
            output[i] = (UTFLOAT)(buf[i] + old_windowed_buf[half_windowsize + i]) / windowsize;
            output[i] *= hinv_buf[i];
        }
        old_windowed_buf[i] = buf[i];
    }
    p->start_pos += p->displace_pos;
}

int ut_paulstretch_create(ut_paulstretch **p)
{
    *p = malloc(sizeof(ut_paulstretch));
    return UT_OK;
}

int ut_paulstretch_destroy(ut_paulstretch **p)
{
    ut_paulstretch *pp = *p;
    ut_auxdata_free(&pp->m_window);
    ut_auxdata_free(&pp->m_old_windowed_buf);
    ut_auxdata_free(&pp->m_hinv_buf);
    ut_auxdata_free(&pp->m_buf);
    ut_auxdata_free(&pp->m_output);
    kiss_fftr_free(pp->fft);
    kiss_fftr_free(pp->ifft);
    KISS_FFT_FREE(pp->tmp1);
    free(*p);
    return UT_OK;
}

int ut_paulstretch_init(ut_data *ut, ut_paulstretch *p, ut_ftbl *ft, UTFLOAT windowsize, UTFLOAT stretch)
{
    uint32_t i;
    p->ft = ft;
    p->windowsize = (uint32_t)(ut->sr * windowsize);
    p->stretch = stretch;
    if(p->windowsize < 16) {
        p->windowsize = 16;
    }
    p->half_windowsize = p->windowsize / 2;
    p->displace_pos = (p->windowsize * 0.5) / p->stretch;

    ut_auxdata_alloc(&p->m_window, sizeof(UTFLOAT) * p->windowsize);
    p->window = p->m_window.ptr;

    ut_auxdata_alloc(&p->m_old_windowed_buf, sizeof(UTFLOAT) * p->windowsize);
    p->old_windowed_buf = p->m_old_windowed_buf.ptr;

    ut_auxdata_alloc(&p->m_hinv_buf, sizeof(UTFLOAT) * p->half_windowsize);
    p->hinv_buf = p->m_hinv_buf.ptr;

    ut_auxdata_alloc(&p->m_buf, sizeof(UTFLOAT) * p->windowsize);
    p->buf = p->m_buf.ptr;

    ut_auxdata_alloc(&p->m_output, sizeof(UTFLOAT) * p->half_windowsize);
    p->output = p->m_output.ptr;

    /* Create Hann window */
    for(i = 0; i < p->windowsize; i++) {
        p->window[i] = 0.5 - cos(i * 2.0 * M_PI / (p->windowsize - 1)) * 0.5;
    }
    /* creatve inverse hann window */
    UTFLOAT hinv_sqrt2 = (1 + sqrt(0.5)) * 0.5;
    for(i = 0; i < p->half_windowsize; i++) {
        p->hinv_buf[i] = hinv_sqrt2 - (1.0 - hinv_sqrt2) * cos(i * 2.0 * M_PI / p->half_windowsize);
    }

    p->start_pos = 0.0;
    p->counter = 0;

    /* set up kissfft */
    p->fft = kiss_fftr_alloc(p->windowsize, 0, NULL, NULL);
    p->ifft = kiss_fftr_alloc(p->windowsize, 1, NULL, NULL);
    kiss_fft_cpx *tmp1 = malloc(sizeof(kiss_fft_cpx) * p->windowsize);
    memset(tmp1, 0, sizeof(UTFLOAT) * p->windowsize);
    p->tmp1 = tmp1;

    /* turn on wrap mode by default */
    p->wrap = 1;
    return UT_OK;
}

int ut_paulstretch_compute(ut_data *ut, ut_paulstretch *p, UTFLOAT *in, UTFLOAT *out)
{
    if(p->counter == 0) {
        compute_block(ut, p);
    }
    *out = p->output[p->counter];
    p->counter = (p->counter + 1) % p->half_windowsize;
    
    return UT_OK;
}
