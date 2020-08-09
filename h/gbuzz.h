typedef struct {
        UTFLOAT amp, freq, nharm, lharm, mul, iphs;
        int16_t ampcod, cpscod, prvn;
        UTFLOAT prvr, twor, rsqp1, rtn, rtnp1, rsumr;
        int32_t lphs;
        int reported;
        UTFLOAT last;
        ut_ftbl *ft;
} ut_gbuzz;

int ut_gbuzz_create(ut_gbuzz **p);
int ut_gbuzz_destroy(ut_gbuzz **p);
int ut_gbuzz_init(ut_data *ut, ut_gbuzz *p, ut_ftbl *ft, UTFLOAT iphs);
int ut_gbuzz_compute(ut_data *ut, ut_gbuzz *p, UTFLOAT *in, UTFLOAT *out);
