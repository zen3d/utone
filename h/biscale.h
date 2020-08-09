typedef struct {
    UTFLOAT min, max;
} ut_biscale;

int ut_biscale_create(ut_biscale **p);
int ut_biscale_destroy(ut_biscale **p);
int ut_biscale_init(ut_data *ut, ut_biscale *p);
int ut_biscale_compute(ut_data *ut, ut_biscale *p, UTFLOAT *in, UTFLOAT *out);
