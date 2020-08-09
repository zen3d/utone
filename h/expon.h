typedef struct {
    UTFLOAT a, dur, b;
    UTFLOAT val, incr; 
    uint32_t sdur, stime;
    int init;
} ut_expon;

int ut_expon_create(ut_expon **p);
int ut_expon_destroy(ut_expon **p);
int ut_expon_init(ut_data *ut, ut_expon *p);
int ut_expon_compute(ut_data *ut, ut_expon *p, UTFLOAT *in, UTFLOAT *out);
