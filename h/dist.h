typedef struct ut_dist{
    UTFLOAT pregain, postgain, shape1, shape2, mode;
} ut_dist;

int ut_dist_create(ut_dist **p);
int ut_dist_destroy(ut_dist **p);
int ut_dist_init(ut_data *ut, ut_dist *p);
int ut_dist_compute(ut_data *ut, ut_dist *p, UTFLOAT *in, UTFLOAT *out);
