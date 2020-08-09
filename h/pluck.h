typedef struct {
    UTFLOAT amp, freq, ifreq;
    UTFLOAT sicps;
    int32_t phs256, npts, maxpts;
    ut_auxdata auxch;
    char init;
} ut_pluck;

int ut_pluck_create(ut_pluck **p);
int ut_pluck_destroy(ut_pluck **p);
int ut_pluck_init(ut_data *ut, ut_pluck *p, UTFLOAT ifreq);
int ut_pluck_compute(ut_data *ut, ut_pluck *p, UTFLOAT *trig, UTFLOAT *out);
