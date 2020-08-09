typedef struct {
    int size, pos;
    UTFLOAT *buf;
} ut_sdelay;

int ut_sdelay_create(ut_sdelay **p);
int ut_sdelay_destroy(ut_sdelay **p);
int ut_sdelay_init(ut_data *ut, ut_sdelay *p, int size);
int ut_sdelay_compute(ut_data *ut, ut_sdelay *p, UTFLOAT *in, UTFLOAT *out);
