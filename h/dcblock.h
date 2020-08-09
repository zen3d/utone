typedef struct {
    UTFLOAT gg;
    UTFLOAT outputs;
    UTFLOAT inputs;
    UTFLOAT gain;
} ut_dcblock;

int ut_dcblock_create(ut_dcblock **p);
int ut_dcblock_destroy(ut_dcblock **p);
int ut_dcblock_init(ut_data *ut, ut_dcblock *p);
int ut_dcblock_compute(ut_data *ut, ut_dcblock *p, UTFLOAT *in, UTFLOAT *out);
