typedef struct {
    void *faust;
    int argpos;
    UTFLOAT *args[3];
    UTFLOAT *shift;
    UTFLOAT *window;
    UTFLOAT *xfade;
} ut_pshift;

int ut_pshift_create(ut_pshift **p);
int ut_pshift_destroy(ut_pshift **p);
int ut_pshift_init(ut_data *ut, ut_pshift *p);
int ut_pshift_compute(ut_data *ut, ut_pshift *p, UTFLOAT *in, UTFLOAT *out);
