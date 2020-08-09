typedef struct {
    void *faust;
    int argpos;
    UTFLOAT *args[4];
    UTFLOAT *ratio;
    UTFLOAT *thresh;
    UTFLOAT *atk;
    UTFLOAT *rel;
} ut_compressor;

int ut_compressor_create(ut_compressor **p);
int ut_compressor_destroy(ut_compressor **p);
int ut_compressor_init(ut_data *ut, ut_compressor *p);
int ut_compressor_compute(ut_data *ut, ut_compressor *p, UTFLOAT *in, UTFLOAT *out);
