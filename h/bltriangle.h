typedef struct {
    void *ud;
    int argpos;
    UTFLOAT *args[2];
    UTFLOAT *freq;
    UTFLOAT *amp;
} ut_bltriangle;

int ut_bltriangle_create(ut_bltriangle **p);
int ut_bltriangle_destroy(ut_bltriangle **p);
int ut_bltriangle_init(ut_data *ut, ut_bltriangle *p);
int ut_bltriangle_compute(ut_data *ut, ut_bltriangle *p, UTFLOAT *in, UTFLOAT *out);

