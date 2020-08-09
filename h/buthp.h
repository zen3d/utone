typedef struct  {
    UTFLOAT sr, freq, istor;
    UTFLOAT lkf;
    UTFLOAT a[8];
    UTFLOAT pidsr;
} ut_buthp;

int ut_buthp_create(ut_buthp **p);
int ut_buthp_destroy(ut_buthp **p);
int ut_buthp_init(ut_data *ut, ut_buthp *p);
int ut_buthp_compute(ut_data *ut, ut_buthp *p, UTFLOAT *in, UTFLOAT *out);
