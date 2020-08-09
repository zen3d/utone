typedef struct {
    void *faust;
    int argpos;
    UTFLOAT *args[11];
    UTFLOAT *in_delay;
    UTFLOAT *lf_x;
    UTFLOAT *rt60_low;
    UTFLOAT *rt60_mid;
    UTFLOAT *hf_damping;
    UTFLOAT *eq1_freq;
    UTFLOAT *eq1_level;
    UTFLOAT *eq2_freq;
    UTFLOAT *eq2_level;
    UTFLOAT *mix;
    UTFLOAT *level;
} ut_zitarev;

int ut_zitarev_create(ut_zitarev **p);
int ut_zitarev_destroy(ut_zitarev **p);
int ut_zitarev_init(ut_data *ut, ut_zitarev *p);
int ut_zitarev_compute(ut_data *ut, ut_zitarev *p, UTFLOAT *in1, UTFLOAT *in2, UTFLOAT *out1, UTFLOAT *out2);

