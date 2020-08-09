typedef struct ut_fof_overlap {
        struct ut_fof_overlap *nxtact, *nxtfree;
        int32_t timrem, dectim, formphs, forminc, risphs, risinc, decphs, decinc;
        UTFLOAT curamp, expamp;
        UTFLOAT glissbas;
        int32_t sampct;
} ut_fof_overlap;

typedef struct {
    UTFLOAT amp, fund, form, oct, band, ris, dur, dec;
    UTFLOAT iolaps, iphs;
    int32_t durtogo, fundphs, fofcount, prvsmps;
    UTFLOAT prvband, expamp, preamp;
    int16_t foftype;        
    int16_t xincod, ampcod, fundcod, formcod, fmtmod;
    ut_auxdata auxch;
    ut_ftbl *ftp1, *ftp2;
    ut_fof_overlap basovrlap;
} ut_fof;

int ut_fof_create(ut_fof **p);
int ut_fof_destroy(ut_fof **p);
int ut_fof_init(ut_data *ut, ut_fof *p, ut_ftbl *sine, ut_ftbl *win, int iolaps, UTFLOAT iphs);
int ut_fof_compute(ut_data *ut, ut_fof *p, UTFLOAT *in, UTFLOAT *out);
