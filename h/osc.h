typedef struct {
    UTFLOAT freq, amp, iphs;
    int32_t   lphs;
    ut_ftbl *tbl;
    int inc;
} ut_osc;

int ut_osc_create(ut_osc **osc);
int ut_osc_destroy(ut_osc **osc);
int ut_osc_init(ut_data *ut, ut_osc *osc, ut_ftbl *ft, UTFLOAT iphs);
int ut_osc_compute(ut_data *ut, ut_osc *osc, UTFLOAT *in, UTFLOAT *out);
