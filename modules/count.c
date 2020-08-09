#include <stdlib.h>
#include "utone.h"

int ut_count_create(ut_count **p)
{
    *p = malloc(sizeof(ut_count));
    return UT_OK;
}

int ut_count_destroy(ut_count **p)
{
    free(*p);
    return UT_OK;
}

int ut_count_init(ut_data *ut, ut_count *p)
{
    p->count = 4;
    p->curcount = -1;
    p->mode = 0;
    return UT_OK;
}

int ut_count_compute(ut_data *ut, ut_count *p, UTFLOAT *in, UTFLOAT *out)
{
    if(*in){
        if(p->mode == 0) {
            p->curcount = (p->curcount + 1) % p->count;
        } else {
            if(p->curcount == -2) {
                *out = -2;
                return UT_OK;
            }
            if(p->curcount >= p->count - 1) {
                p->curcount = -2;
            } else {
                if(p->curcount == -1) p->curcount = 0;
                else p->curcount++;
            }
        }
    }
    *out = p->curcount;
    return UT_OK;
}
