typedef struct {
    UTFLOAT pan;
    uint32_t type;
} ut_panst;

int ut_panst_create(ut_panst **p);
int ut_panst_destroy(ut_panst **p);
int ut_panst_init(ut_data *ut, ut_panst *p);
int ut_panst_compute(ut_data *ut, ut_panst *p, UTFLOAT *in1, UTFLOAT *in2, UTFLOAT *out1, UTFLOAT *out2);
