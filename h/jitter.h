typedef struct ut_jitter{
    UTFLOAT amp, cpsMin, cpsMax;
    UTFLOAT cps;
    int32_t phs;
    int initflag;
    UTFLOAT num1, num2, dfdmax;
} ut_jitter;

int ut_jitter_create(ut_jitter **p);
int ut_jitter_destroy(ut_jitter **p);
int ut_jitter_init(ut_data *ut, ut_jitter *p);
int ut_jitter_compute(ut_data *ut, ut_jitter *p, UTFLOAT *in, UTFLOAT *out);
