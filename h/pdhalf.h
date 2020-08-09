typedef struct {
    UTFLOAT amount, ibipolar, ifullscale;
} ut_pdhalf;

int ut_pdhalf_create(ut_pdhalf **p);
int ut_pdhalf_destroy(ut_pdhalf **p);
int ut_pdhalf_init(ut_data *ut, ut_pdhalf *p);
int ut_pdhalf_compute(ut_data *ut, ut_pdhalf *p, UTFLOAT *in, UTFLOAT *out);
