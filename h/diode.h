typedef struct {
    /* 4 one-pole filters */
    UTFLOAT opva_alpha[4];
    UTFLOAT opva_beta[4];
    UTFLOAT opva_gamma[4];
    UTFLOAT opva_delta[4];
    UTFLOAT opva_eps[4];
    UTFLOAT opva_a0[4];
    UTFLOAT opva_fdbk[4];
    UTFLOAT opva_z1[4];
    /* end one-pole filters */

    UTFLOAT SG[4];
    UTFLOAT gamma;
    UTFLOAT freq;
    UTFLOAT K;
    UTFLOAT res;
} ut_diode;

int ut_diode_create(ut_diode **p);
int ut_diode_destroy(ut_diode **p);
int ut_diode_init(ut_data *ut, ut_diode *p);
int ut_diode_compute(ut_data *ut, ut_diode *p, UTFLOAT *in, UTFLOAT *out);
