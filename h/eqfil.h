typedef struct {
  UTFLOAT freq, bw, gain;
  UTFLOAT z1,z2, sr;
  UTFLOAT frv, bwv;
  UTFLOAT c,d;
} ut_eqfil;

int ut_eqfil_create(ut_eqfil **p);
int ut_eqfil_destroy(ut_eqfil **p);
int ut_eqfil_init(ut_data *ut, ut_eqfil *p);
int ut_eqfil_compute(ut_data *ut, ut_eqfil *p, UTFLOAT *in, UTFLOAT *out);
