typedef struct {
    UTFLOAT hp;
    UTFLOAT c1, c2, yt1, prvhp;
    UTFLOAT tpidsr;
} ut_atone;

int ut_atone_create(ut_atone **p);
int ut_atone_destroy(ut_atone **p);
int ut_atone_init(ut_data *ut, ut_atone *p);
int ut_atone_compute(ut_data *ut, ut_atone *p, UTFLOAT *in, UTFLOAT *out);
