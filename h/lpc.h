typedef struct {
    struct openlpc_e_state *e;
    struct openlpc_d_state *d;
    int counter;
    short *in;
    short *out;
    unsigned char data[7];
    UTFLOAT y[7];
    UTFLOAT smooth;
    UTFLOAT samp;
    unsigned int clock;
    unsigned int block;
    int framesize;
    ut_auxdata m_in;
    ut_auxdata m_out;
    ut_auxdata m_e;
    ut_auxdata m_d;
    int mode;
    ut_ftbl *ft;
} ut_lpc;

int ut_lpc_create(ut_lpc **lpc);
int ut_lpc_destroy(ut_lpc **lpc);
int ut_lpc_init(ut_data *ut, ut_lpc *lpc, int framesize);
int ut_lpc_synth(ut_data *ut, ut_lpc *lpc, ut_ftbl *ft);
int ut_lpc_compute(ut_data *ut, ut_lpc *lpc, UTFLOAT *in, UTFLOAT *out);
