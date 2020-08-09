typedef struct {
    UTFLOAT beg,dur,end;
    uint32_t steps;
    uint32_t count;
    UTFLOAT val;
    UTFLOAT type;
    UTFLOAT slope;
    UTFLOAT tdivnsteps;
} ut_tseg;

int ut_tseg_create(ut_tseg **p);
int ut_tseg_destroy(ut_tseg **p);
int ut_tseg_init(ut_data *ut, ut_tseg *p, UTFLOAT ibeg);
int ut_tseg_compute(ut_data *ut, ut_tseg *p, UTFLOAT *in, UTFLOAT *out);
