typedef struct {
    UTFLOAT atk, rel, thresh;
    UTFLOAT patk, prel;
	UTFLOAT b0_r, a1_r, b0_a, a1_a, level;
} ut_peaklim;

int ut_peaklim_create(ut_peaklim **p);
int ut_peaklim_destroy(ut_peaklim **p);
int ut_peaklim_init(ut_data *ut, ut_peaklim *p);
int ut_peaklim_compute(ut_data *ut, ut_peaklim *p, UTFLOAT *in, UTFLOAT *out);
