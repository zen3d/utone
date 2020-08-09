typedef struct {
    UTFLOAT amp;
    unsigned int newrand;
    unsigned int prevrand;
    unsigned int k;
    unsigned int seed;
    unsigned int total;
    uint32_t counter;
    unsigned int dice[7];
} ut_pinknoise;

int ut_pinknoise_create(ut_pinknoise **p);
int ut_pinknoise_destroy(ut_pinknoise **p);
int ut_pinknoise_init(ut_data *ut, ut_pinknoise *p);
int ut_pinknoise_compute(ut_data *ut, ut_pinknoise *p, UTFLOAT *in, UTFLOAT *out);

