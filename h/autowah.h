typedef struct {
    void *faust;
    int argpos;
    UTFLOAT *args[3];
    UTFLOAT *level;
    UTFLOAT *wah;
    UTFLOAT *mix;
} ut_autowah;

int ut_autowah_create(ut_autowah **p);
int ut_autowah_destroy(ut_autowah **p);
int ut_autowah_init(ut_data *ut, ut_autowah *p);
int ut_autowah_compute(ut_data *ut, ut_autowah *p, UTFLOAT *in, UTFLOAT *out);
