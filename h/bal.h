typedef struct ut_bal{
    UTFLOAT asig, csig, ihp;
    UTFLOAT c1, c2, prvq, prvr, prva;
} ut_bal;

int ut_bal_create(ut_bal **p);
int ut_bal_destroy(ut_bal **p);
int ut_bal_init(ut_data *ut, ut_bal *p);
int ut_bal_compute(ut_data *ut, ut_bal *p, UTFLOAT *sig, UTFLOAT *comp, UTFLOAT *out);
