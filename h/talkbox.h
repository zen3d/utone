
#ifndef UT_TALKBOX_BUFMAX
#define UT_TALKBOX_BUFMAX 1600
#endif

typedef struct {
    UTFLOAT quality;
    UTFLOAT d0, d1, d2, d3, d4;
    UTFLOAT u0, u1, u2, u3, u4;
    UTFLOAT FX;
    UTFLOAT emphasis;
    UTFLOAT car0[UT_TALKBOX_BUFMAX]; 
    UTFLOAT car1[UT_TALKBOX_BUFMAX];
    UTFLOAT window[UT_TALKBOX_BUFMAX];
    UTFLOAT buf0[UT_TALKBOX_BUFMAX];
    UTFLOAT buf1[UT_TALKBOX_BUFMAX];
    uint32_t K, N, O, pos;
} ut_talkbox;

int ut_talkbox_create(ut_talkbox **p);
int ut_talkbox_destroy(ut_talkbox **p);
int ut_talkbox_init(ut_data *ut, ut_talkbox *p);
int ut_talkbox_compute(ut_data *ut, ut_talkbox *p, UTFLOAT *src, UTFLOAT *exc, UTFLOAT *out);
