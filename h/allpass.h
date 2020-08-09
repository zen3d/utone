typedef struct {
    UTFLOAT revtime, looptime;
    UTFLOAT coef, prvt;
    ut_auxdata aux;
    uint32_t bufpos;
    uint32_t bufsize;
} ut_allpass;

int ut_allpass_create(ut_allpass **p);
int ut_allpass_destroy(ut_allpass **p);
int ut_allpass_init(ut_data *ut, ut_allpass *p, UTFLOAT looptime);
int ut_allpass_compute(ut_data *ut, ut_allpass *p, UTFLOAT *in, UTFLOAT *out);
