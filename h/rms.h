typedef struct ut_rms{
    UTFLOAT ihp, istor;
    UTFLOAT c1, c2, prvq;
} ut_rms;

int ut_rms_create(ut_rms **p);
int ut_rms_destroy(ut_rms **p);
int ut_rms_init(ut_data *ut, ut_rms *p);
int ut_rms_compute(ut_data *ut, ut_rms *p, UTFLOAT *in, UTFLOAT *out);
