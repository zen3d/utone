typedef struct {
    UTFLOAT imincps, imaxcps, icps;
    UTFLOAT imedi, idowns, iexcps, irmsmedi;
    UTFLOAT srate;
    UTFLOAT lastval;
    int32_t downsamp;
    int32_t upsamp;
    int32_t minperi;
    int32_t maxperi;
    int32_t index;
    int32_t readp;
    int32_t size;
    int32_t peri;
    int32_t medisize;
    int32_t mediptr;
    int32_t rmsmedisize;
    int32_t rmsmediptr;
    int inerr;
    ut_auxdata median;
    ut_auxdata rmsmedian;
    ut_auxdata buffer;
} ut_pitchamdf;

int ut_pitchamdf_create(ut_pitchamdf **p);
int ut_pitchamdf_destroy(ut_pitchamdf **p);
int ut_pitchamdf_init(ut_data *ut, ut_pitchamdf *p, UTFLOAT imincps, UTFLOAT imaxcps);
int ut_pitchamdf_compute(ut_data *ut, ut_pitchamdf *p, UTFLOAT *in, UTFLOAT *cps, UTFLOAT *rms);
