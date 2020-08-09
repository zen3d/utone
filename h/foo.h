typedef struct {
    UTFLOAT bar;
} ut_foo;

int ut_foo_create(ut_foo **p);
int ut_foo_destroy(ut_foo **p);
int ut_foo_init(ut_data *ut, ut_foo *p);
int ut_foo_compute(ut_data *ut, ut_foo *p, UTFLOAT *in, UTFLOAT *out);
