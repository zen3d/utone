typedef struct {
    UTFLOAT time;
    uint32_t counter;
} ut_dmetro;

int ut_dmetro_create(ut_dmetro **p);
int ut_dmetro_destroy(ut_dmetro **p);
int ut_dmetro_init(ut_data *ut, ut_dmetro *p);
int ut_dmetro_compute(ut_data *ut, ut_dmetro *p, UTFLOAT *in, UTFLOAT *out);
