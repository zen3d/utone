typedef struct {
    uint32_t windowsize;
    uint32_t half_windowsize;
    UTFLOAT stretch;
    UTFLOAT start_pos;
    UTFLOAT displace_pos;
    UTFLOAT *window;
    UTFLOAT *old_windowed_buf;
    UTFLOAT *hinv_buf;
    UTFLOAT *buf;
    UTFLOAT *output;
    ut_ftbl *ft;
    kiss_fftr_cfg fft, ifft;
    kiss_fft_cpx *tmp1, *tmp2;
    uint32_t counter;
    ut_auxdata m_window;
    ut_auxdata m_old_windowed_buf;
    ut_auxdata m_hinv_buf;
    ut_auxdata m_buf;
    ut_auxdata m_output;
    unsigned char wrap;
} ut_paulstretch;

int ut_paulstretch_create(ut_paulstretch **p);
int ut_paulstretch_destroy(ut_paulstretch **p);
int ut_paulstretch_init(ut_data *ut, ut_paulstretch *p, ut_ftbl *ft, UTFLOAT windowsize, UTFLOAT stretch);
int ut_paulstretch_compute(ut_data *ut, ut_paulstretch *p, UTFLOAT *in, UTFLOAT *out);
