typedef struct {
    UTFLOAT bitdepth;
    UTFLOAT srate;
    ut_fold *fold;
} ut_bitcrush;

int ut_bitcrush_create(ut_bitcrush **p);
int ut_bitcrush_destroy(ut_bitcrush **p);
int ut_bitcrush_init(ut_data *ut, ut_bitcrush *p);
int ut_bitcrush_compute(ut_data *ut, ut_bitcrush *p, UTFLOAT *in, UTFLOAT *out);
