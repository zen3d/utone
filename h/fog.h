typedef struct ut_fog_overlap {
    struct ut_fog_overlap *nxtact;
    struct ut_fog_overlap *nxtfree;
    int32_t timrem, dectim, formphs, forminc;
    uint32_t risphs;
    int32_t risinc, decphs, decinc;
    UTFLOAT curamp, expamp;
    UTFLOAT pos, inc;
} ut_fog_overlap;

typedef struct {
    UTFLOAT amp, dens, trans, spd, oct, band, ris, dur, dec;
    UTFLOAT iolaps, iphs, itmode;
    ut_fog_overlap basovrlap;
    int32_t durtogo, fundphs, fofcount, prvsmps, spdphs;
    UTFLOAT prvband, expamp, preamp, fogcvt; 
    int16_t formcod, fmtmod, speedcod;
    ut_auxdata auxch;
    ut_ftbl *ftp1, *ftp2;
} ut_fog;

int ut_fog_create(ut_fog **p);
int ut_fog_destroy(ut_fog **p);
int ut_fog_init(ut_data *ut, ut_fog *p, ut_ftbl *wav, ut_ftbl *win, int iolaps, UTFLOAT iphs);
int ut_fog_compute(ut_data *ut, ut_fog *p, UTFLOAT *in, UTFLOAT *out);
