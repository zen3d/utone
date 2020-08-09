#include <stdlib.h>
#include "utone.h"

int ut_switch_create(ut_switch **p)
{
    *p = malloc(sizeof(ut_switch));
    return UT_OK;
}

int ut_switch_destroy(ut_switch **p)
{
    free(*p);
    return UT_OK;
}

int ut_switch_init(ut_data *ut, ut_switch *p)
{
    p->mode = 0;
    return UT_OK;
}

int ut_switch_compute(ut_data *ut, ut_switch *p, UTFLOAT *trig,
    UTFLOAT *in1, UTFLOAT *in2, UTFLOAT *out)
{
    if (*trig) {
        p->mode = p->mode == 0 ? 1 : 0;
    }

    if(p->mode == 0) {
        *out = *in1;
    } else {
        *out = *in2;
    }

    return UT_OK;
}
