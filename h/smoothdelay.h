typedef struct {
    UTFLOAT del, maxdel, pdel;
    UTFLOAT sr;
    UTFLOAT feedback;

    int counter;
    int maxcount;

    uint32_t maxbuf;

    ut_auxdata buf1;
    uint32_t bufpos1;
    uint32_t deltime1;

    ut_auxdata buf2;
    uint32_t bufpos2;
    uint32_t deltime2;
    int curbuf;
} ut_smoothdelay;

int ut_smoothdelay_create(ut_smoothdelay **p);
int ut_smoothdelay_destroy(ut_smoothdelay **p);
int ut_smoothdelay_init(ut_data *ut, ut_smoothdelay *p, 
        UTFLOAT maxdel, uint32_t interp);
int ut_smoothdelay_compute(ut_data *ut, ut_smoothdelay *p, UTFLOAT *in, UTFLOAT *out);
