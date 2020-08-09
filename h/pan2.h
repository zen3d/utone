typedef struct {
    UTFLOAT pan;
    uint32_t type;
} ut_pan2;

int ut_pan2_create(ut_pan2 **p);
int ut_pan2_destroy(ut_pan2 **p);
int ut_pan2_init(ut_data *ut, ut_pan2 *p);
int ut_pan2_compute(ut_data *ut, ut_pan2 *p, UTFLOAT *in, UTFLOAT *out1, UTFLOAT *out2);
