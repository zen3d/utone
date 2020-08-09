typedef struct {
    UTFLOAT sig;
    UTFLOAT index, mode, offset, wrap;
    UTFLOAT mul;
    ut_ftbl *ft;
} ut_tabread;

int ut_tabread_create(ut_tabread **p);
int ut_tabread_destroy(ut_tabread **p);
int ut_tabread_init(ut_data *ut, ut_tabread *p, ut_ftbl *ft, int mode);
int ut_tabread_compute(ut_data *ut, ut_tabread *p, UTFLOAT *in, UTFLOAT *out);
