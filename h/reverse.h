typedef struct  {
    UTFLOAT delay;
    uint32_t bufpos;
    uint32_t bufsize;
    ut_auxdata buf;
} ut_reverse;

int ut_reverse_create(ut_reverse **p);
int ut_reverse_destroy(ut_reverse **p); 
int ut_reverse_init(ut_data *ut, ut_reverse *p, UTFLOAT delay);
int ut_reverse_compute(ut_data *ut, ut_reverse *p, UTFLOAT *in, UTFLOAT *out);
