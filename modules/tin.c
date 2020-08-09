#include <stdlib.h>
#include "utone.h"

int ut_tin_create(ut_tin **p)
{
    *p = malloc(sizeof(ut_tin));
    return UT_OK;
}

int ut_tin_destroy(ut_tin **p)
{
    free(*p);
    return UT_OK;
}

int ut_tin_init(ut_data *ut, ut_tin *p)
{
    p->fp = stdin; 
    p->val = 0;
    return UT_OK;
}

int ut_tin_compute(ut_data *ut, ut_tin *p, UTFLOAT *in, UTFLOAT *out)
{
    if(*in) {
        fread(&p->val, sizeof(UTFLOAT), 1, p->fp);
    }

    *out = p->val;
    return UT_OK;
}
