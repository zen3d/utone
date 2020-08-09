typedef struct {
    UTFLOAT min, max;
} ut_scale;

int ut_scale_create(ut_scale **p);
int ut_scale_destroy(ut_scale **p);
int ut_scale_init(ut_data *ut, ut_scale *p);
int ut_scale_compute(ut_data *ut, ut_scale *p, UTFLOAT *in, UTFLOAT *out);
