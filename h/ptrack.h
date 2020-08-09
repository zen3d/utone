typedef struct {
    UTFLOAT freq, amp;
    UTFLOAT asig,size,peak;
    ut_auxdata signal, prev, sin, spec1, spec2, peakarray;
    int numpks;
    int cnt;
    int histcnt;
    int hopsize;
    UTFLOAT sr;
    UTFLOAT cps;
    UTFLOAT dbs[20];
    UTFLOAT amplo;
    UTFLOAT amphi;
    UTFLOAT npartial;
    UTFLOAT dbfs;
    UTFLOAT prevf;
    ut_fft fft;
} ut_ptrack;

int ut_ptrack_create(ut_ptrack **p);
int ut_ptrack_destroy(ut_ptrack **p);
int ut_ptrack_init(ut_data *ut, ut_ptrack *p, int ihopsize, int ipeaks);
int ut_ptrack_compute(ut_data *ut, ut_ptrack *p, UTFLOAT *in, UTFLOAT *freq, UTFLOAT *amp);
