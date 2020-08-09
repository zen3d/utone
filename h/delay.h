typedef struct {
    UTFLOAT time;
    UTFLOAT feedback;
    UTFLOAT last;
    ut_auxdata buf;
    uint32_t bufsize;
    uint32_t bufpos;
} ut_delay;

int ut_delay_create(ut_delay **p);
int ut_delay_destroy(ut_delay **p);
int ut_delay_init(ut_data *ut, ut_delay *p, UTFLOAT time);
int ut_delay_compute(ut_data *ut, ut_delay *p, UTFLOAT *in, UTFLOAT *out);
