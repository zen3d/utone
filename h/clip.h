typedef struct{
    UTFLOAT lim, k1;
}ut_clip;

int ut_clip_create(ut_clip **p);
int ut_clip_destroy(ut_clip **p);
int ut_clip_init(ut_data *ut, ut_clip *p);
int ut_clip_compute(ut_data *ut, ut_clip *p, UTFLOAT *in, UTFLOAT *out);
