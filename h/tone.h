typedef struct {
    UTFLOAT hp;
    UTFLOAT c1, c2, yt1, prvhp;
    UTFLOAT tpidsr;
} ut_tone;

int ut_tone_create(ut_tone **t);
int ut_tone_destroy(ut_tone **t);
int ut_tone_init(ut_data *ut, ut_tone *t);
int ut_tone_compute(ut_data *ut, ut_tone *t, UTFLOAT *in, UTFLOAT *out);
