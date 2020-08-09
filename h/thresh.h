typedef struct {
    int init;
    UTFLOAT prev, thresh, mode;
} ut_thresh;

int ut_thresh_create(ut_thresh **p);
int ut_thresh_destroy(ut_thresh **p);
int ut_thresh_init(ut_data *ut, ut_thresh *p);
int ut_thresh_compute(ut_data *ut, ut_thresh *p, UTFLOAT *in, UTFLOAT *out);
