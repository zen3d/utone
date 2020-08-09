typedef struct {
    UTFLOAT time;
    uint32_t timer;
} ut_tgate;

int ut_tgate_create(ut_tgate **p);
int ut_tgate_destroy(ut_tgate **p);
int ut_tgate_init(ut_data *ut, ut_tgate *p);
int ut_tgate_compute(ut_data *ut, ut_tgate *p, UTFLOAT *in, UTFLOAT *out);
