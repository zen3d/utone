typedef struct {
    UTFLOAT time, amp, pitch, lock, iN,
        idecim, onset, offset, dbthresh;
    int cnt, hsize, curframe, N, decim,tscale;
    UTFLOAT pos;
    UTFLOAT accum;
    ut_auxdata outframe, win, bwin, fwin,
    nwin, prev, framecount, indata[2];
    UTFLOAT *tab;
    int curbuf;
    UTFLOAT resamp;
    ut_ftbl *ft;
    ut_fft fft;
} ut_mincer;

int ut_mincer_create(ut_mincer **p);
int ut_mincer_destroy(ut_mincer **p);
int ut_mincer_init(ut_data *ut, ut_mincer *p, ut_ftbl *ft, int winsize);
int ut_mincer_compute(ut_data *ut, ut_mincer *p, UTFLOAT *in, UTFLOAT *out);
