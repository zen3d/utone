#define UT_FT_MAXLEN 0x1000000L
#define UT_FT_PHMASK 0x0FFFFFFL

typedef struct ut_ftbl{
    size_t size;
    uint32_t lobits;
    uint32_t lomask;
    UTFLOAT lodiv;
    UTFLOAT sicvt;
    UTFLOAT *tbl;
    char del;
}ut_ftbl;

int ut_ftbl_create(ut_data *ut, ut_ftbl **ft, size_t size);
int ut_ftbl_init(ut_data *ut, ut_ftbl *ft, size_t size);
int ut_ftbl_bind(ut_data *ut, ut_ftbl **ft, UTFLOAT *tbl, size_t size);
int ut_ftbl_destroy(ut_ftbl **ft);
int ut_gen_vals(ut_data *ut, ut_ftbl *ft, const char *string);
int ut_gen_sine(ut_data *ut, ut_ftbl *ft);
int ut_gen_file(ut_data *ut, ut_ftbl *ft, const char *filename);
int ut_gen_sinesum(ut_data *ut, ut_ftbl *ft, const char *argstring);
int ut_gen_line(ut_data *ut, ut_ftbl *ft, const char *argstring);
int ut_gen_xline(ut_data *ut, ut_ftbl *ft, const char *argstring);
int ut_gen_gauss(ut_data *ut, ut_ftbl *ft, UTFLOAT scale, uint32_t seed);
int ut_ftbl_loadfile(ut_data *ut, ut_ftbl **ft, const char *filename);
int ut_ftbl_loadspa(ut_data *ut, ut_ftbl **ft, const char *filename);
int ut_gen_composite(ut_data *ut, ut_ftbl *ft, const char *argstring);
int ut_gen_rand(ut_data *ut, ut_ftbl *ft, const char *argstring);
int ut_gen_triangle(ut_data *ut, ut_ftbl *ft);
