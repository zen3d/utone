typedef struct {
    void *faust;
    int argpos;
    UTFLOAT *args[3];
    UTFLOAT *atk;
    UTFLOAT *rel;
    UTFLOAT *bwratio;
} ut_vocoder;

int ut_vocoder_create(ut_vocoder **p);
int ut_vocoder_destroy(ut_vocoder **p);
int ut_vocoder_init(ut_data *ut, ut_vocoder *p);
int ut_vocoder_compute(ut_data *ut, ut_vocoder *p, UTFLOAT *source, UTFLOAT *excite, UTFLOAT *out);

