typedef struct {
    uint32_t num, counter, offset;
} ut_tdiv;

int ut_tdiv_create(ut_tdiv **p);
int ut_tdiv_destroy(ut_tdiv **p);
int ut_tdiv_init(ut_data *ut, ut_tdiv *p);
int ut_tdiv_compute(ut_data *ut, ut_tdiv *p, UTFLOAT *in, UTFLOAT *out);
