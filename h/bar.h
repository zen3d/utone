typedef struct {
    UTFLOAT bcL, bcR, iK, ib, scan, T30;
    UTFLOAT pos, vel, wid;

    UTFLOAT *w, *w1, *w2;
    int step, first;
    UTFLOAT s0, s1, s2, t0, t1;
    int i_bcL, i_bcR, N;
    ut_auxdata w_aux;
} ut_bar;

int ut_bar_create(ut_bar **p);
int ut_bar_destroy(ut_bar **p);
int ut_bar_init(ut_data *ut, ut_bar *p, UTFLOAT iK, UTFLOAT ib);
int ut_bar_compute(ut_data *ut, ut_bar *p, UTFLOAT *in, UTFLOAT *out);
