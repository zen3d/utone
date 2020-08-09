typedef struct {
    UTFLOAT freq, amp, iphs;
    ut_ftbl *tbl;
    int32_t tablen;
    UTFLOAT tablenUPsr;
    UTFLOAT phs;
    UTFLOAT onedsr;
} ut_posc3;

int ut_posc3_create(ut_posc3 **posc3);
int ut_posc3_destroy(ut_posc3 **posc3);
int ut_posc3_init(ut_data *ut, ut_posc3 *posc3, ut_ftbl *ft);
int ut_posc3_compute(ut_data *ut, ut_posc3 *posc3, UTFLOAT *in, UTFLOAT *out);
