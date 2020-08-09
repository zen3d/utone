typedef struct {
    UTFLOAT bpm;
    UTFLOAT subdiv;
    uint32_t counter;
} ut_clock;

int ut_clock_create(ut_clock **p);
int ut_clock_destroy(ut_clock **p);
int ut_clock_init(ut_data *ut, ut_clock *p);
int ut_clock_compute(ut_data *ut, ut_clock *p, UTFLOAT *trig, UTFLOAT *out);
