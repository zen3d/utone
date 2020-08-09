typedef struct ut_wavout ut_wavout;
int ut_wavout_create(ut_wavout **p);
int ut_wavout_destroy(ut_wavout **p);
int ut_wavout_init(ut_data *ut, ut_wavout *p, const char *filename);
int ut_wavout_compute(ut_data *ut, ut_wavout *p, UTFLOAT *in, UTFLOAT *out);
