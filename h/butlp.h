typedef struct  {
    UTFLOAT sr, freq, istor;
    UTFLOAT lkf;
    UTFLOAT a[8];
    UTFLOAT pidsr;
} ut_butlp;

int ut_butlp_create(ut_butlp **p);
int ut_butlp_destroy(ut_butlp **p);
int ut_butlp_init(ut_data *ut, ut_butlp *p);
int ut_butlp_compute(ut_data *ut, ut_butlp *p, UTFLOAT *in, UTFLOAT *out);
