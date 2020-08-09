#include <stdlib.h>
#include <math.h>
#include "utone.h"

#ifndef M_PI
#define M_PI		3.14159265358979323846
#endif

#define SQRT2 1.41421356237309504880


int ut_panst_create(ut_panst **p)
{
    *p = malloc(sizeof(ut_panst));
    return UT_OK;
}

int ut_panst_destroy(ut_panst **p)
{
    free(*p);
    return UT_OK;
}

int ut_panst_init(ut_data *ut, ut_panst *p)
{
    p->type = 0;
    p->pan = 0;
    return UT_OK;
}

int ut_panst_compute(ut_data *ut, ut_panst *p, UTFLOAT *in1, UTFLOAT *in2, UTFLOAT *out1, UTFLOAT *out2)
{
    /* Send the signal's input to the output */
    uint32_t type = p->type;
    UTFLOAT pan = (p->pan + 1.0) * 0.5;
    UTFLOAT cc, ss, l, r;

    type %= 4;

    switch (type) {
        /* Equal power */
        case 0:
        pan = M_PI * 0.5 * pan;
        *out1 = *in1 * cos(pan);
        *out2 = *in2 * sin(pan);
        break;

        /* Square root */
        case 1:
        *out1 = *in1 * sqrt(pan);
        *out2 = *in2 * sqrt(1.0 - pan);
        break;

        /* simple linear */
        case 2:
        *out1 = *in1 * (1.0 - pan);
        *out2 = *in2 * pan;
        break;

        /* Equal power (alternative) */
        case 3:

        cc = cos(M_PI * pan * 0.5);
        ss = sin(M_PI * pan * 0.5);
        l = SQRT2 * (cc + ss) * 0.5;
        r = SQRT2 * (cc - ss) * 0.5;
        *out1 = *in1 * l;
        *out2 = *in2 * r;
        break;
    }

    return UT_OK;
}
