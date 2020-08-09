typedef struct{
    UTFLOAT htime;
    UTFLOAT c1, c2, yt1, prvhtim;
    UTFLOAT sr, onedsr;
}ut_port;

int ut_port_create(ut_port **p);
int ut_port_destroy(ut_port **p);
int ut_port_init(ut_data *ut, ut_port *p, UTFLOAT htime);
int ut_port_compute(ut_data *ut, ut_port *p, UTFLOAT *in, UTFLOAT *out);
int ut_port_reset(ut_data *ut, ut_port *p, UTFLOAT *in);
