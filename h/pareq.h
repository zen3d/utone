typedef struct {
    UTFLOAT fc, v, q, mode;

    UTFLOAT xnm1, xnm2, ynm1, ynm2;
    UTFLOAT prv_fc, prv_v, prv_q;
    UTFLOAT b0, b1, b2, a1, a2;
    UTFLOAT tpidsr;
    int imode;
} ut_pareq;

int ut_pareq_create(ut_pareq **p);
int ut_pareq_destroy(ut_pareq **p);
int ut_pareq_init(ut_data *ut, ut_pareq *p);
int ut_pareq_compute(ut_data *ut, ut_pareq *p, UTFLOAT *in, UTFLOAT *out);
