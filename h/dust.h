typedef struct ut_dust{
    UTFLOAT amp, density; 
    UTFLOAT density0, thresh, scale;
    UTFLOAT onedsr;
    int bipolar; /* 1 = bipolar 0 = unipolar */
    uint32_t rand;
} ut_dust;

int ut_dust_create(ut_dust **p);
int ut_dust_destroy(ut_dust **p);
int ut_dust_init(ut_data *ut, ut_dust *p);
int ut_dust_compute(ut_data *ut, ut_dust *p, UTFLOAT *in, UTFLOAT *out);


