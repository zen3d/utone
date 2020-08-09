#include <stdlib.h>
#include "utone.h"

int ut_thresh_create(ut_thresh **p)
{
    *p = malloc(sizeof(ut_thresh));
    return UT_OK;
}

int ut_thresh_destroy(ut_thresh **p)
{
    free(*p);
    return UT_OK;
}

int ut_thresh_init(ut_data *ut, ut_thresh *p)
{
    /* Initalize variables here. */
    p->init = 1;
    p->mode = 0;
    p->prev = 0;
    p->thresh = 0;
    return UT_OK;
}

int ut_thresh_compute(ut_data *ut, ut_thresh *p, UTFLOAT *in, UTFLOAT *out)
{
    if(p->init) {
        *out = 0;
        p->prev = *in;
        p->init = 0;
        return UT_OK;
    }

    switch((int)p->mode) {
        /* input signal goes above threshold */
        case 0:
            *out = (*in > p->thresh && p->prev <= p->thresh);
            break;

        /* input signal goes below threshold */
        case 1:
            *out = (*in < p->thresh && p->prev >= p->thresh);
            break;

        /* input signal goes below or above threshold */
        case 2:
            *out = (*in < p->thresh && p->prev >= p->thresh) ||
                (*in > p->thresh && p->prev <= p->thresh);
            break;

        default:
            return UT_NOT_OK;
    }

    p->prev = *in;
    
    return UT_OK;
}
