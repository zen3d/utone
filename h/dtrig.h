typedef struct ut_dtrig{
    ut_ftbl *ft;
    uint32_t counter;
    uint32_t pos;
    int running;
    int loop;
    UTFLOAT delay;
    UTFLOAT scale;
} ut_dtrig;

int ut_dtrig_create(ut_dtrig **p);
int ut_dtrig_destroy(ut_dtrig **p);
int ut_dtrig_init(ut_data *ut, ut_dtrig *p, ut_ftbl *ft);
int ut_dtrig_compute(ut_data *ut, ut_dtrig *p, UTFLOAT *in, UTFLOAT *out);
