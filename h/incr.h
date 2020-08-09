typedef struct {
    UTFLOAT step;
    UTFLOAT min;
    UTFLOAT max;
    UTFLOAT val;
} ut_incr;

int ut_incr_create(ut_incr **p);
int ut_incr_destroy(ut_incr **p);
int ut_incr_init(ut_data *ut, ut_incr *p, UTFLOAT val);
int ut_incr_compute(ut_data *ut, ut_incr *p, UTFLOAT *in, UTFLOAT *out);
