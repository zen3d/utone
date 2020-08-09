typedef struct {
    FILE *fp;
} ut_in;

int ut_in_create(ut_in **p);
int ut_in_destroy(ut_in **p);
int ut_in_init(ut_data *ut, ut_in *p);
int ut_in_compute(ut_data *ut, ut_in *p, UTFLOAT *in, UTFLOAT *out);
