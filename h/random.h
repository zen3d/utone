typedef struct { 
    UTFLOAT min;
    UTFLOAT max;
} ut_random;

int ut_random_create(ut_random **p);
int ut_random_destroy(ut_random **p);
int ut_random_init(ut_data *ut, ut_random *p);
int ut_random_compute(ut_data *ut, ut_random *p, UTFLOAT *in, UTFLOAT *out);
