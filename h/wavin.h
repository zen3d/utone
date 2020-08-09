typedef struct ut_wavin ut_wavin;
int ut_wavin_create(ut_wavin **p);
int ut_wavin_destroy(ut_wavin **p);
int ut_wavin_init(ut_data *ut, ut_wavin *p, const char *filename);
int ut_wavin_compute(ut_data *ut, ut_wavin *p, UTFLOAT *in, UTFLOAT *out);
