typedef struct {
    UTFLOAT incr;
    UTFLOAT index;
    int32_t sample_index;
    UTFLOAT value;
} ut_fold;

int ut_fold_create(ut_fold **p);
int ut_fold_destroy(ut_fold **p);
int ut_fold_init(ut_data *ut, ut_fold *p);
int ut_fold_compute(ut_data *ut, ut_fold *p, UTFLOAT *in, UTFLOAT *out);
