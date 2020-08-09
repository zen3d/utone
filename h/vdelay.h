typedef struct ut_vdelay{
    UTFLOAT del, maxdel;
    UTFLOAT feedback;
    UTFLOAT prev;
    UTFLOAT sr;
    ut_auxdata buf;
    int32_t left;
} ut_vdelay;

int ut_vdelay_create(ut_vdelay **p);
int ut_vdelay_destroy(ut_vdelay **p);
int ut_vdelay_init(ut_data *ut, ut_vdelay *p, UTFLOAT maxdel);
int ut_vdelay_compute(ut_data *ut, ut_vdelay *p, UTFLOAT *in, UTFLOAT *out);
int ut_vdelay_reset(ut_data *ut, ut_vdelay *p);
