typedef struct{
    UTFLOAT amp;
}ut_noise;

int ut_noise_create(ut_noise **ns);
int ut_noise_init(ut_data *ut, ut_noise *ns);
int ut_noise_compute(ut_data *ut, ut_noise *ns, UTFLOAT *in, UTFLOAT *out);
int ut_noise_destroy(ut_noise **ns);
