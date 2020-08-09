typedef struct {
    UTFLOAT brown;
} ut_brown;

int ut_brown_create(ut_brown **p);
int ut_brown_destroy(ut_brown **p);
int ut_brown_init(ut_data *ut, ut_brown *p);
int ut_brown_compute(ut_data *ut, ut_brown *p, UTFLOAT *in, UTFLOAT *out);
