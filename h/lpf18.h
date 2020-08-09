typedef struct ut_lpf18{
    UTFLOAT cutoff, res, dist;
    UTFLOAT ay1, ay2, aout, lastin, onedsr;
} ut_lpf18;

int ut_lpf18_create(ut_lpf18 **p);
int ut_lpf18_destroy(ut_lpf18 **p);
int ut_lpf18_init(ut_data *ut, ut_lpf18 *p);
int ut_lpf18_compute(ut_data *ut, ut_lpf18 *p, UTFLOAT *in, UTFLOAT *out);
