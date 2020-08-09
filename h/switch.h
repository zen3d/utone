typedef struct {
    UTFLOAT mode;
} ut_switch;

int ut_switch_create(ut_switch **p);
int ut_switch_destroy(ut_switch **p);
int ut_switch_init(ut_data *ut, ut_switch *p);
int ut_switch_compute(ut_data *ut, ut_switch *p, UTFLOAT *trig,
    UTFLOAT *in1, UTFLOAT *in2, UTFLOAT *out);
