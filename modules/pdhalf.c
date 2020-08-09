/*
 * PDHalf
 *
 * This code has been extracted from the Csound opcode "pdhalf".
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): Anthony M. Kozar Jr.
 * Year: 2004
 * Location: Opcodes/shape.c
 */

#include <stdlib.h>
#include "utone.h"

int ut_pdhalf_create(ut_pdhalf **p)
{
    *p = malloc(sizeof(ut_pdhalf));
    return UT_OK;
}

int ut_pdhalf_destroy(ut_pdhalf **p)
{
    free(*p);
    return UT_OK;
}

int ut_pdhalf_init(ut_data *ut, ut_pdhalf *p)
{
    p->ibipolar = 0;
    p->ifullscale = 1.0;
    p->amount = 0;
    return UT_OK;
}

int ut_pdhalf_compute(ut_data *ut, ut_pdhalf *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT cur, maxampl, midpoint, leftslope, rightslope;

    maxampl = p->ifullscale;
    if (maxampl == 0.0)  maxampl = 1.0;

    if (p->ibipolar != 0.0) {
        midpoint =  (p->amount >= 1.0 ? maxampl :
                    (p->amount <= -1.0 ? -maxampl :
                    (p->amount * maxampl)));

    if (midpoint != -maxampl) 
        leftslope  = maxampl / (midpoint + maxampl);
    else leftslope  = 0.0;
    if (midpoint != maxampl)  
        rightslope = maxampl / (maxampl - midpoint);
    else rightslope = 0.0;

    cur = *in;
    if (cur < midpoint) *out = leftslope * (cur - midpoint);
    else *out = rightslope * (cur - midpoint);
    } else {
        UTFLOAT halfmaxampl = 0.5 * maxampl;
        midpoint =  (p->amount >= 1.0 ? maxampl :
                    (p->amount <= -1.0 ? 0.0 :
                    ((p->amount + 1.0) * halfmaxampl)));

        if (midpoint != 0.0) 
            leftslope = halfmaxampl / midpoint;
        else leftslope  = 0.0;
        if (midpoint != maxampl) 
            rightslope = halfmaxampl / (maxampl - midpoint);
        else rightslope = 0.0;

        cur = *in;
        if (cur < midpoint) { 
            *out = leftslope * cur;
        } else { 
            *out = rightslope * (cur - midpoint) + halfmaxampl;
        }
    }

    return UT_OK;
}
