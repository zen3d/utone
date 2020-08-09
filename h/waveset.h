typedef struct {
    UTFLOAT rep, len;
    ut_auxdata auxch;
    int32_t length;
    int32_t cnt;
    int32_t start;
    int32_t current;
    int32_t direction;
    int32_t end;
    UTFLOAT lastsamp;
    int32_t  noinsert;
} ut_waveset;

int ut_waveset_create(ut_waveset **p);
int ut_waveset_destroy(ut_waveset **p);
int ut_waveset_init(ut_data *ut, ut_waveset *p, UTFLOAT ilen);
int ut_waveset_compute(ut_data *ut, ut_waveset *p, UTFLOAT *in, UTFLOAT *out);
