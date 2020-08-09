typedef struct {
    UTFLOAT freq, bw;
    int scale;
    UTFLOAT c1, c2, c3, yt1, yt2, cosf, prvfreq, prvbw;
    UTFLOAT tpidsr;
} ut_reson;

int ut_reson_create(ut_reson **p);
int ut_reson_destroy(ut_reson **p);
int ut_reson_init(ut_data *ut, ut_reson *p);
int ut_reson_compute(ut_data *ut, ut_reson *p, UTFLOAT *in, UTFLOAT *out);
