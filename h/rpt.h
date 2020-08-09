typedef struct ut_rpt{
    uint32_t playpos;
    uint32_t bufpos;
    int running;
    int count, reps;
    UTFLOAT sr;
    uint32_t size;
    UTFLOAT bpm;
    int div, rep;
    ut_auxdata aux;
    int rc;
} ut_rpt;

int ut_rpt_create(ut_rpt **p);
int ut_rpt_destroy(ut_rpt **p);
int ut_rpt_init(ut_data *ut, ut_rpt *p, UTFLOAT maxdur);
int ut_rpt_compute(ut_data *ut, ut_rpt *p, UTFLOAT *trig, 
        UTFLOAT *in, UTFLOAT *out);
