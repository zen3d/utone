typedef struct ut_fosc{
    UTFLOAT amp, freq, car, mod, indx, iphs;
    int32_t mphs, cphs;
    ut_ftbl *ft;
} ut_fosc;

int ut_fosc_create(ut_fosc **p);
int ut_fosc_destroy(ut_fosc **p);
int ut_fosc_init(ut_data *ut, ut_fosc *p, ut_ftbl *ft);
int ut_fosc_compute(ut_data *ut, ut_fosc *p, UTFLOAT *in, UTFLOAT *out);
