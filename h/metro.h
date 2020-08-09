typedef struct ut_metro{
    UTFLOAT sr, freq, iphs;
    UTFLOAT curphs;
    int flag;
    UTFLOAT onedsr;
} ut_metro;

int ut_metro_create(ut_metro **p);
int ut_metro_destroy(ut_metro **p);
int ut_metro_init(ut_data *ut, ut_metro *p);
int ut_metro_compute(ut_data *ut, ut_metro *p, UTFLOAT *in, UTFLOAT *out);
