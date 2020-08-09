typedef struct {
    UTFLOAT *buf;
    uint32_t pos;
    uint32_t bufsize;
    ut_audio uta;
    ut_auxdata aux;
} ut_utarec;

int ut_utarec_create(ut_utarec **p);
int ut_utarec_destroy(ut_utarec **p);
int ut_utarec_init(ut_data *ut, ut_utarec *p, const char *filename);
int ut_utarec_compute(ut_data *ut, ut_utarec *p, UTFLOAT *in, UTFLOAT *out);
int ut_utarec_close(ut_data *ut, ut_utarec *p);
