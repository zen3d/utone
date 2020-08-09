typedef struct {
    int     writePos;
    int     bufferSize;
    int     readPos;
    int     readPosFrac;
    int     readPosFrac_inc;
    int     dummy;
    int     seedVal;
    int     randLine_cnt;
    UTFLOAT filterState;
    UTFLOAT *buf;
} ut_revsc_dl;

typedef struct  {
    UTFLOAT feedback, lpfreq;
    UTFLOAT iSampleRate, iPitchMod, iSkipInit;
    UTFLOAT sampleRate;
    UTFLOAT dampFact;
    UTFLOAT prv_LPFreq;
    int initDone;
    ut_revsc_dl delayLines[8];
    ut_auxdata aux;
} ut_revsc;

int ut_revsc_create(ut_revsc **p);
int ut_revsc_destroy(ut_revsc **p);
int ut_revsc_init(ut_data *ut, ut_revsc *p);
int ut_revsc_compute(ut_data *ut, ut_revsc *p, UTFLOAT *in1, UTFLOAT *in2, UTFLOAT *out1, UTFLOAT *out2);
