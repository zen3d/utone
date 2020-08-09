typedef struct {
    FILE *fp;
    UTFLOAT val;
} ut_tin;

int ut_tin_create(ut_tin **p);
int ut_tin_destroy(ut_tin **p);
int ut_tin_init(ut_data *ut, ut_tin *p);
int ut_tin_compute(ut_data *ut, ut_tin *p, UTFLOAT *in, UTFLOAT *out);
