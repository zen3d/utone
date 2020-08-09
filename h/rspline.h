typedef struct {
    UTFLOAT min, max, cps_min, cps_max;
    UTFLOAT si;
    UTFLOAT phs;
    int rmin_cod, rmax_cod;
    UTFLOAT num0, num1, num2, df0, df1, c3, c2;
    UTFLOAT onedsr;
    int holdrand;
    int init;
} ut_rspline;

int ut_rspline_create(ut_rspline **p);
int ut_rspline_destroy(ut_rspline **p);
int ut_rspline_init(ut_data *ut, ut_rspline *p);
int ut_rspline_compute(ut_data *ut, ut_rspline *p, UTFLOAT *in, UTFLOAT *out);
