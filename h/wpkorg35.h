typedef struct {
    /* LPF1 */
    UTFLOAT lpf1_a;
    UTFLOAT lpf1_z;
    
    /* LPF2 */
    UTFLOAT lpf2_a;
    UTFLOAT lpf2_b;
    UTFLOAT lpf2_z;
    
    /* HPF */
    UTFLOAT hpf_a;
    UTFLOAT hpf_b;
    UTFLOAT hpf_z;

    UTFLOAT alpha;

    UTFLOAT cutoff;
    UTFLOAT res;
    UTFLOAT saturation;

    UTFLOAT pcutoff;
    UTFLOAT pres;

    uint32_t nonlinear;
} ut_wpkorg35;

int ut_wpkorg35_create(ut_wpkorg35 **p);
int ut_wpkorg35_destroy(ut_wpkorg35 **p);
int ut_wpkorg35_init(ut_data *ut, ut_wpkorg35 *p);
int ut_wpkorg35_compute(ut_data *ut, ut_wpkorg35 *p, UTFLOAT *in, UTFLOAT *out);
