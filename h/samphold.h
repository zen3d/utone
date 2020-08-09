typedef struct {
    UTFLOAT val;
} ut_samphold;

int ut_samphold_create(ut_samphold **p);
int ut_samphold_destroy(ut_samphold **p);
int ut_samphold_init(ut_data *ut, ut_samphold *p);
int ut_samphold_compute(ut_data *ut, ut_samphold *p, UTFLOAT *trig, UTFLOAT *in, UTFLOAT *out);
