#include <stdlib.h>
#include "utone.h"

enum {
    T_ON,
    T_OFF,
    T_INIT
};

int ut_tenv2_create(ut_tenv2 **p)
{
    *p = malloc(sizeof(ut_tenv2));
    return UT_OK;
}

int ut_tenv2_destroy(ut_tenv2 **p)
{
    free(*p);
    return UT_OK;
}

int ut_tenv2_init(ut_data *ut, ut_tenv2 *p)
{
    p->state = T_INIT;
    p->atk = 0.1;
    p->rel = 0.1;
    p->slope = 0;
    p->last = 0;
    return UT_OK;
}

int ut_tenv2_compute(ut_data *ut, ut_tenv2 *p, UTFLOAT *in, UTFLOAT *out)
{
    if(*in != 0) {
        if(p->state == T_INIT || p->state == T_OFF) {
            p->state = T_ON;
            p->timer = (uint32_t)(ut->sr * p->atk);
            p->totaltime = p->timer;
            p->slope = 1.0 / p->totaltime;
        } else if (p->state == T_ON) { 
            p->state = T_OFF;
            p->timer = (uint32_t)(ut->sr * p->rel);
            p->totaltime = p->timer;
            p->slope = 1.0 / p->totaltime;
        }
    }
    if(p->timer == 0) {
        if(p->state == T_ON) *out = 1;
        else *out = 0;
        return UT_OK;
    } else {
        p->timer--;
        if(p->state == T_ON)  {
            *out = p->last + p->slope;
        } else if (p->state == T_OFF) {
            *out = p->last - p->slope;
        }

        if(*out > 1) *out = 1;
        if(*out < 0) *out = 0;

        p->last = *out;

        return UT_OK;
    }
    return UT_OK;
}
