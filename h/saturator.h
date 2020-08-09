typedef struct
{
    UTFLOAT drive;
    UTFLOAT dcoffset;

    UTFLOAT dcblocker[2][7];

    UTFLOAT ai[6][7];
    UTFLOAT aa[6][7];
} ut_saturator;

int ut_saturator_create(ut_saturator **p);
int ut_saturator_destroy(ut_saturator **p);
int ut_saturator_init(ut_data *ut, ut_saturator *p);
int ut_saturator_compute(ut_data *ut, ut_saturator *p, UTFLOAT *in, UTFLOAT *out);
