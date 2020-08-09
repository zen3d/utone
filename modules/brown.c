/*
 * Brown
 * 
 * Brownian noise algorithm based on implementation found here:
 * http://vellocet.com/dsp/noise/VRand.h
 * 
 * 
 */

#include <stdlib.h>
#include "utone.h"

int ut_brown_create(ut_brown **p)
{
    *p = malloc(sizeof(ut_brown));
    return UT_OK;
}

int ut_brown_destroy(ut_brown **p)
{
    free(*p);
    return UT_OK;
}

int ut_brown_init(ut_data *ut, ut_brown *p)
{
    p->brown = 0.0;
    return UT_OK;
}

int ut_brown_compute(ut_data *ut, ut_brown *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT r;
    while(1) {
        r = (ut_rand(ut) % UT_RANDMAX) / (UTFLOAT)(UT_RANDMAX);
        r = ((r * 2) - 1) * 0.5;
        p->brown += r;
        if(p->brown < -8.0f || p->brown > 8.0f) {
            p->brown -= r;
        } else {
            break;
        }
    }

    *out = p->brown * 0.0625;
    return UT_OK;
}
