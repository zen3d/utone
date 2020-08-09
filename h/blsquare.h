typedef struct {
    void *ud;
    int argpos;
    UTFLOAT *args[3];
    UTFLOAT *freq;
    UTFLOAT *amp;
    UTFLOAT *width;
} ut_blsquare;

int ut_blsquare_create(ut_blsquare **p);
int ut_blsquare_destroy(ut_blsquare **p);
int ut_blsquare_init(ut_data *ut, ut_blsquare *p);
int ut_blsquare_compute(ut_data *ut, ut_blsquare *p, UTFLOAT *in, UTFLOAT *out);
