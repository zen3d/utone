typedef struct {
    UTFLOAT sr, freq, bw, istor;
    UTFLOAT lkf, lkb;
    UTFLOAT a[8];
    UTFLOAT pidsr, tpidsr;
} ut_butbp;

int ut_butbp_create(ut_butbp **p);
int ut_butbp_destroy(ut_butbp **p);
int ut_butbp_init(ut_data *ut, ut_butbp *p);
int ut_butbp_compute(ut_data *ut, ut_butbp *p, UTFLOAT *in, UTFLOAT *out);
