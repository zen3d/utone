#include <stdlib.h>
#include "utone.h"

int ut_dmetro_create(ut_dmetro **p)
{
    *p = malloc(sizeof(ut_dmetro));
    return UT_OK;
}

int ut_dmetro_destroy(ut_dmetro **p)
{
    free(*p);
    return UT_OK;
}

int ut_dmetro_init(ut_data *ut, ut_dmetro *p)
{
    p->counter = 0;
    p->time = 1.0;
    return UT_OK;
}

int ut_dmetro_compute(ut_data *ut, ut_dmetro *p, UTFLOAT *in, UTFLOAT *out)
{
    *out = 0; 

    if(p->counter == 0) {
        *out = 1.0;
        p->counter = (int)(ut->sr * p->time) + 1;
    }

    p->counter--; 

    return UT_OK;
}
