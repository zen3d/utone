typedef struct {
    UTFLOAT a, dur, b;
    UTFLOAT val, incr; 
    uint32_t sdur, stime;
    int init;
} ut_line;

int ut_line_create(ut_line **p);
int ut_line_destroy(ut_line **p);
int ut_line_init(ut_data *ut, ut_line *p);
int ut_line_compute(ut_data *ut, ut_line *p, UTFLOAT *in, UTFLOAT *out);
