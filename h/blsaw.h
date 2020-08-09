typedef struct {
    void *ud;
    int argpos;
    UTFLOAT *args[2];
    UTFLOAT *freq;
    UTFLOAT *amp;
} ut_blsaw;

int ut_blsaw_create(ut_blsaw **p);
int ut_blsaw_destroy(ut_blsaw **p);
int ut_blsaw_init(ut_data *ut, ut_blsaw *p);
int ut_blsaw_compute(ut_data *ut, ut_blsaw *p, UTFLOAT *in, UTFLOAT *out);
