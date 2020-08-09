typedef struct {
    UTFLOAT pos;
} ut_crossfade;

int ut_crossfade_create(ut_crossfade **p);
int ut_crossfade_destroy(ut_crossfade **p);
int ut_crossfade_init(ut_data *ut, ut_crossfade *p);
int ut_crossfade_compute(ut_data *ut, ut_crossfade *p, UTFLOAT *in1, UTFLOAT *in2, UTFLOAT *out);
