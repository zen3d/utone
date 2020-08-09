typedef struct {
    int mode;
    uint32_t pos;
    UTFLOAT time;
} ut_timer;

int ut_timer_create(ut_timer **p);
int ut_timer_destroy(ut_timer **p);
int ut_timer_init(ut_data *ut, ut_timer *p);
int ut_timer_compute(ut_data *ut, ut_timer *p, UTFLOAT *in, UTFLOAT *out);
