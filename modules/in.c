#include <stdlib.h>
#include "utone.h"

int ut_in_create(ut_in **p)
{
    *p = malloc(sizeof(ut_in));
    return UT_OK;
}

int ut_in_destroy(ut_in **p)
{
    ut_in *pp = *p;
    fclose(pp->fp);
    free(*p);
    return UT_OK;
}

int ut_in_init(ut_data *ut, ut_in *p)
{
    p->fp = stdin; 
    return UT_OK;
}

int ut_in_compute(ut_data *ut, ut_in *p, UTFLOAT *in, UTFLOAT *out)
{
    *out = 0;
    fread(out, sizeof(UTFLOAT), 1, p->fp);
    return UT_OK;
}
