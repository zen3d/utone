typedef struct{
    UTFLOAT freq, q, xnm1, ynm1, ynm2, a0, a1, a2, d, lfq, lq;
    UTFLOAT sr;
}ut_mode;

int ut_mode_create(ut_mode **p);
int ut_mode_destroy(ut_mode **p);
int ut_mode_init(ut_data *ut, ut_mode *p);
int ut_mode_compute(ut_data *ut, ut_mode *p, UTFLOAT *in, UTFLOAT *out);
