typedef struct {
    UTFLOAT min, max, val;
} ut_trand;

int ut_trand_create(ut_trand **p);
int ut_trand_destroy(ut_trand **p);
int ut_trand_init(ut_data *ut, ut_trand *p);
int ut_trand_compute(ut_data *ut, ut_trand *p, UTFLOAT *in, UTFLOAT *out);
