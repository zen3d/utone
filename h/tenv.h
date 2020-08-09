typedef struct ut_tenv{
    ut_tevent *te;
    uint32_t pos, atk_end, rel_start, sr, totaldur;
    UTFLOAT atk, rel, hold;
    UTFLOAT atk_slp, rel_slp;
    UTFLOAT last;
    int sigmode;
    UTFLOAT input;
} ut_tenv;

int ut_tenv_create(ut_tenv **p);
int ut_tenv_destroy(ut_tenv **p);
int ut_tenv_init(ut_data *ut, ut_tenv *p);
int ut_tenv_compute(ut_data *ut, ut_tenv *p, UTFLOAT *in, UTFLOAT *out);
