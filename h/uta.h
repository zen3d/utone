typedef struct {
    UTFLOAT *buf;
    uint32_t pos;
    uint32_t bufsize;
    ut_audio uta;
    ut_auxdata aux;
} ut_uta;

int ut_uta_create(ut_uta **p);
int ut_uta_destroy(ut_uta **p);
int ut_uta_init(ut_data *ut, ut_uta *p, const char *filename);
int ut_uta_compute(ut_data *ut, ut_uta *p, UTFLOAT *in, UTFLOAT *out);
