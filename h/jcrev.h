typedef struct {
    void *ud;
} ut_jcrev;

int ut_jcrev_create(ut_jcrev **p);
int ut_jcrev_destroy(ut_jcrev **p);
int ut_jcrev_init(ut_data *ut, ut_jcrev *p);
int ut_jcrev_compute(ut_data *ut, ut_jcrev *p, UTFLOAT *in, UTFLOAT *out);
