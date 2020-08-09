typedef struct{
    UTFLOAT fco, res, dist, asym, iskip, y, y1, y2;
    int fcocod, rezcod;
    UTFLOAT sr;
    UTFLOAT onedsr;

}ut_tbvcf;

int ut_tbvcf_create(ut_tbvcf **p);
int ut_tbvcf_destroy(ut_tbvcf **p);
int ut_tbvcf_init(ut_data *ut, ut_tbvcf *p);
int ut_tbvcf_compute(ut_data *ut, ut_tbvcf *p, UTFLOAT *in, UTFLOAT *out);
