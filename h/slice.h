typedef struct {
    ut_ftbl *vals;
    ut_ftbl *buf;
    uint32_t id;
    uint32_t pos;
    uint32_t nextpos;
} ut_slice;

int ut_slice_create(ut_slice **p);
int ut_slice_destroy(ut_slice **p);
int ut_slice_init(ut_data *ut, ut_slice *p, ut_ftbl *vals, ut_ftbl *buf);
int ut_slice_compute(ut_data *ut, ut_slice *p, UTFLOAT *in, UTFLOAT *out);
