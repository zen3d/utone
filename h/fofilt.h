typedef struct{
    UTFLOAT freq, atk, dec, istor;
    UTFLOAT tpidsr;
    UTFLOAT sr;
    UTFLOAT delay[4];
}ut_fofilt;

int ut_fofilt_create(ut_fofilt **t);
int ut_fofilt_destroy(ut_fofilt **t);
int ut_fofilt_init(ut_data *ut, ut_fofilt *p);
int ut_fofilt_compute(ut_data *ut, ut_fofilt *p, UTFLOAT *in, UTFLOAT *out);

