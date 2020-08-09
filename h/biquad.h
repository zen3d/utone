typedef struct{
    UTFLOAT b0, b1, b2, a0, a1, a2, reinit, xnm1, xnm2, ynm1, ynm2, cutoff, res;
    UTFLOAT sr;
    UTFLOAT tpidsr;
}ut_biquad;

int ut_biquad_create(ut_biquad **p);
int ut_biquad_destroy(ut_biquad **p);
int ut_biquad_init(ut_data *ut, ut_biquad *p);
int ut_biquad_compute(ut_data *ut, ut_biquad *p, UTFLOAT *in, UTFLOAT *out);
