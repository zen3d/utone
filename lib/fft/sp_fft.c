void ut_fft_init(ut_fft *fft, int M)
{
    UTFLOAT *utbl;
    int16_t *BRLow;
    int16_t *BRLowCpx;
    int i;

    /* init cos table */
    utbl = (UTFLOAT*) malloc((POW2(M) / 4 + 1) * sizeof(UTFLOAT));
    fftCosInit(M, utbl);

    BRLowCpx =
      (int16_t*) malloc(POW2(M / 2 - 1) * sizeof(int16_t));
    fftBRInit(M, BRLowCpx);

    /* init bit reversed table for real FFT */
     BRLow =
      (int16_t*) malloc(POW2((M - 1) / 2 - 1) * sizeof(int16_t));
    fftBRInit(M - 1, BRLow);

    fft->BRLow = BRLow;
    fft->BRLowCpx = BRLowCpx;
    fft->utbl = utbl;
}

void ut_fftr(ut_fft *fft, UTFLOAT *buf, int FFTsize)
{
    UTFLOAT *Utbl;
    int16_t *BRLow;
    int   M = log2(FFTsize);
    rffts1(buf, M, fft->utbl, fft->BRLow);
}

void ut_fft_cpx(ut_fft *fft, UTFLOAT *buf, int FFTsize)
{
    UTFLOAT *Utbl;
    int16_t *BRLow;
    int   M = log2(FFTsize);
    ffts1(buf, M, fft->utbl, fft->BRLowCpx);
}



void ut_ifftr(ut_fft *fft, UTFLOAT *buf, int FFTsize)
{
    UTFLOAT *Utbl;
    int16_t *BRLow;
    int   M = log2(FFTsize);
    riffts1(buf, M, fft->utbl, fft->BRLow);
}

void ut_fft_destroy(ut_fft *fft) 
{
    free(fft->utbl);
    free(fft->BRLow);
    free(fft->BRLowCpx);
}
