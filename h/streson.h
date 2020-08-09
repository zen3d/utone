typedef struct{
    UTFLOAT freq, fdbgain;
    UTFLOAT LPdelay, APdelay;
    UTFLOAT *Cdelay;
    ut_auxdata buf;
    int wpointer, rpointer, size;
}ut_streson;

int ut_streson_create(ut_streson **p);
int ut_streson_destroy(ut_streson **p);
int ut_streson_init(ut_data *ut, ut_streson *p);
int ut_streson_compute(ut_data *ut, ut_streson *p, UTFLOAT *in, UTFLOAT *out);
