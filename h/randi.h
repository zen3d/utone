typedef struct {
    UTFLOAT min, max, cps, mode, fstval;
    int16_t cpscod;
    int32_t phs;
    UTFLOAT num1, num2, dfdmax;
    int holdrand;
    UTFLOAT sicvt;
} ut_randi;

int ut_randi_create(ut_randi **p);
int ut_randi_destroy(ut_randi **p);
int ut_randi_init(ut_data *ut, ut_randi *p);
int ut_randi_compute(ut_data *ut, ut_randi *p, UTFLOAT *in, UTFLOAT *out);
