typedef struct {
    UTFLOAT atk;
    UTFLOAT dec;
    UTFLOAT sus;
    UTFLOAT rel;
    uint32_t timer;
    uint32_t atk_time;
    UTFLOAT a;
    UTFLOAT b;
    UTFLOAT y;
    UTFLOAT x;
    UTFLOAT prev;
    int mode;
} ut_adsr;

int ut_adsr_create(ut_adsr **p);
int ut_adsr_destroy(ut_adsr **p);
int ut_adsr_init(ut_data *ut, ut_adsr *p);
int ut_adsr_compute(ut_data *ut, ut_adsr *p, UTFLOAT *in, UTFLOAT *out);
