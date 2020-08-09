typedef struct ut_tseq {
    ut_ftbl *ft;
    UTFLOAT val;
    int32_t pos;
    int shuf;
} ut_tseq;

int ut_tseq_create(ut_tseq **p);
int ut_tseq_destroy(ut_tseq **p);
int ut_tseq_init(ut_data *ut, ut_tseq *p, ut_ftbl *ft);
int ut_tseq_compute(ut_data *ut, ut_tseq *p, UTFLOAT *trig, UTFLOAT *val);
