typedef struct ut_phasor{
    UTFLOAT freq, phs;
    UTFLOAT curphs, onedsr;
} ut_phasor;

int ut_phasor_create(ut_phasor **p);
int ut_phasor_destroy(ut_phasor **p);
int ut_phasor_init(ut_data *ut, ut_phasor *p, UTFLOAT iphs);
int ut_phasor_compute(ut_data *ut, ut_phasor *p, UTFLOAT *in, UTFLOAT *out);
