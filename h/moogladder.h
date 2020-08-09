typedef struct {
    UTFLOAT freq;
    UTFLOAT res;
    UTFLOAT istor;

    UTFLOAT delay[6];
    UTFLOAT tanhstg[3];
    UTFLOAT oldfreq;
    UTFLOAT oldres;
    UTFLOAT oldacr;
    UTFLOAT oldtune;
} ut_moogladder;

int ut_moogladder_create(ut_moogladder **t);
int ut_moogladder_destroy(ut_moogladder **t);
int ut_moogladder_init(ut_data *ut, ut_moogladder *p);
int ut_moogladder_compute(ut_data *ut, ut_moogladder *p, UTFLOAT *in, UTFLOAT *out);
