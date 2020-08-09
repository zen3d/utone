typedef struct ut_maygate{
    UTFLOAT prob;
    UTFLOAT gate;
    int mode;
} ut_maygate;

int ut_maygate_create(ut_maygate **p);
int ut_maygate_destroy(ut_maygate **p);
int ut_maygate_init(ut_data *ut, ut_maygate *p);
int ut_maygate_compute(ut_data *ut, ut_maygate *p, UTFLOAT *in, UTFLOAT *out);
