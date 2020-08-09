typedef struct {
    UTFLOAT freq;
    UTFLOAT min, max;
    UTFLOAT val;
    uint32_t counter, dur;
} ut_randh;

int ut_randh_create(ut_randh **p);
int ut_randh_destroy(ut_randh **p);
int ut_randh_init(ut_data *ut, ut_randh *p);
int ut_randh_compute(ut_data *ut, ut_randh *p, UTFLOAT *in, UTFLOAT *out);
