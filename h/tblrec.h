typedef struct {
    ut_ftbl *ft;
    uint32_t index;
    int record;
} ut_tblrec;

int ut_tblrec_create(ut_tblrec **p);
int ut_tblrec_destroy(ut_tblrec **p);
int ut_tblrec_init(ut_data *ut, ut_tblrec *p, ut_ftbl *ft);
int ut_tblrec_compute(ut_data *ut, ut_tblrec *p, UTFLOAT *in, UTFLOAT *trig, UTFLOAT *out);
