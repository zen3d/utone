typedef struct {
    int nbars, skip;
    int counter;
    uint32_t len;
} ut_progress;

int ut_progress_create(ut_progress **p);
int ut_progress_destroy(ut_progress **p);
int ut_progress_init(ut_data *ut, ut_progress *p);
int ut_progress_compute(ut_data *ut, ut_progress *p, UTFLOAT *in, UTFLOAT *out);
