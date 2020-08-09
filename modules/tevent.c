#include <stdlib.h>
#include "utone.h"

int ut_tevent_create(ut_tevent **te)
{
    *te = malloc(sizeof(ut_tevent));
    return UT_NOT_OK;
}

int ut_tevent_destroy(ut_tevent **te)
{
    free(*te);
    return UT_NOT_OK;
}

int ut_tevent_init(ut_data *ut, ut_tevent *te, 
        void (*reinit)(void*), void (*compute)(void *, UTFLOAT *out), void *ud)
{
    te->reinit = reinit;
    te->compute = compute;
    te->ud = ud;
    te->started = 0;
    return UT_OK;
}

int ut_tevent_compute(ut_data *ut, ut_tevent *te, UTFLOAT *in, UTFLOAT *out)
{
    if(*in){
        te->reinit(te->ud);
        te->started = 1;
    }
    if(te->started) {
        te->compute(te->ud, out);
    }
    else {
        *out = 0;
    }

    return UT_OK;
}
