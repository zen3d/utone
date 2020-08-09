#include <stdlib.h>
#include "utone.h"

int ut_randh_create(ut_randh **p)
{
    *p = malloc(sizeof(ut_randh));
    return UT_OK;
}

int ut_randh_destroy(ut_randh **p)
{
    free(*p);
    return UT_OK;
}

int ut_randh_init(ut_data *ut, ut_randh *p)
{
    p->counter = 0;
    p->freq = 10;
    p->dur = (ut->sr / p->freq);
    p->min = 0;
    p->max = 1;
    p->val = 0;
    return UT_OK;
}

int ut_randh_compute(ut_data *ut, ut_randh *p, UTFLOAT *in, UTFLOAT *out)
{
    if(p->counter == 0) {
        p->val = p->min + ((UTFLOAT) ut_rand(ut) / UT_RANDMAX) * (p->max - p->min);
        
        if(p->freq == 0) {
            p->dur = 1;
        } else {
            p->dur = (ut->sr / p->freq) + 1; 
        }

        *out = p->val;
    } else {
        *out = p->val;
    }
    p->counter = (p->counter + 1) % p->dur;
    return UT_OK;
}
