typedef struct {
    UTFLOAT value;
    UTFLOAT target;
    UTFLOAT rate;
    int state;
    UTFLOAT attackRate;
    UTFLOAT decayRate;
    UTFLOAT sustainLevel;
    UTFLOAT releaseRate;
    UTFLOAT atk;
    UTFLOAT rel;
    UTFLOAT sus;
    UTFLOAT dec;
    int mode;
} ut_tadsr;

int ut_tadsr_create(ut_tadsr **p);
int ut_tadsr_destroy(ut_tadsr **p);
int ut_tadsr_init(ut_data *ut, ut_tadsr *p);
int ut_tadsr_compute(ut_data *ut, ut_tadsr *p, UTFLOAT *trig, UTFLOAT *out);
