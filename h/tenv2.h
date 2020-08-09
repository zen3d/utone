typedef struct {
    int state;
    UTFLOAT atk, rel;
    uint32_t totaltime;
    uint32_t timer;
    UTFLOAT slope;
    UTFLOAT last;
} ut_tenv2;

int ut_tenv2_create(ut_tenv2 **p);
int ut_tenv2_destroy(ut_tenv2 **p);
int ut_tenv2_init(ut_data *ut, ut_tenv2 *p);
int ut_tenv2_compute(ut_data *ut, ut_tenv2 *p, UTFLOAT *in, UTFLOAT *out);
