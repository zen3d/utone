typedef struct ut_tenvx{
    UTFLOAT atk, rel, hold;
    UTFLOAT patk, prel;
    uint32_t count;
    UTFLOAT a_a, b_a;
    UTFLOAT a_r, b_r;
    UTFLOAT y;
} ut_tenvx;

int ut_tenvx_create(ut_tenvx **p);
int ut_tenvx_destroy(ut_tenvx **p);
int ut_tenvx_init(ut_data *ut, ut_tenvx *p);
int ut_tenvx_compute(ut_data *ut, ut_tenvx *p, UTFLOAT *in, UTFLOAT *out);
