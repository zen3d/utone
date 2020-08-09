typedef struct ut_count{
    int32_t count, curcount;
    int mode;
} ut_count;

int ut_count_create(ut_count **p);
int ut_count_destroy(ut_count **p);
int ut_count_init(ut_data *ut, ut_count *p);
int ut_count_compute(ut_data *ut, ut_count *p, UTFLOAT *in, UTFLOAT *out);
