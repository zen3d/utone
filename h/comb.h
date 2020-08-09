typedef struct ut_comb{
    UTFLOAT revtime, looptime;
    UTFLOAT coef, prvt;
    ut_auxdata aux;
    uint32_t bufpos;
    uint32_t bufsize;
} ut_comb;

int ut_comb_create(ut_comb **p);
int ut_comb_destroy(ut_comb **p);
int ut_comb_init(ut_data *ut, ut_comb *p, UTFLOAT looptime);
int ut_comb_compute(ut_data *ut, ut_comb *p, UTFLOAT *in, UTFLOAT *out);
