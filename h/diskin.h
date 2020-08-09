typedef struct ut_diskin ut_diskin;
int ut_diskin_create(ut_diskin **p);
int ut_diskin_destroy(ut_diskin **p);
int ut_diskin_init(ut_data *ut, ut_diskin *p, const char *filename);
int ut_diskin_compute(ut_data *ut, ut_diskin *p, UTFLOAT *in, UTFLOAT *out);
