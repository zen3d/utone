typedef struct {
    UTFLOAT sr, freq, bw, istor;
    UTFLOAT lkf, lkb;
    UTFLOAT a[8];
    UTFLOAT pidsr, tpidsr;
} ut_butbr;

int ut_butbr_create(ut_butbr **p);
int ut_butbr_destroy(ut_butbr **p);
int ut_butbr_init(ut_data *ut, ut_butbr *p);
int ut_butbr_compute(ut_data *ut, ut_butbr *p, UTFLOAT *in, UTFLOAT *out);
