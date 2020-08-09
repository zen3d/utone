typedef struct {
    UTFLOAT xnm1[12], ynm1[12], coef[12];
} ut_hilbert;

int ut_hilbert_create(ut_hilbert **p);
int ut_hilbert_destroy(ut_hilbert **p);
int ut_hilbert_init(ut_data *ut, ut_hilbert *p);
int ut_hilbert_compute(ut_data *ut, ut_hilbert *p, UTFLOAT *in, UTFLOAT *out1, UTFLOAT *out2);
