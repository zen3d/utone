typedef struct {
    UTFLOAT freq, amp, iphs;
    int32_t lphs;
    ut_ftbl **tbl;
    int inc;
    UTFLOAT wtpos;
    int nft;
} ut_oscmorph;

int ut_oscmorph_create(ut_oscmorph **p);
int ut_oscmorph_destroy(ut_oscmorph **p);
int ut_oscmorph_init(ut_data *ut, ut_oscmorph *osc, ut_ftbl **ft, int nft, UTFLOAT iphs);
int ut_oscmorph_compute(ut_data *ut, ut_oscmorph *p, UTFLOAT *in, UTFLOAT *out);
