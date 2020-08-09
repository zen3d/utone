#include <stdlib.h>
#include "utone.h"

int ut_dtrig_create(ut_dtrig **p)
{
    *p = malloc(sizeof(ut_dtrig));
    return UT_OK;
}

int ut_dtrig_destroy(ut_dtrig **p)
{
    free(*p);
    return UT_OK;
}

int ut_dtrig_init(ut_data *ut, ut_dtrig *p, ut_ftbl *ft)
{
    p->ft = ft;
    p->counter = 0;
    p->pos = 0; 
    p->running = 0;
    p->loop = 0;
    p->delay = 0;
    p->scale = 1;
    return UT_OK;
}

int ut_dtrig_compute(ut_data *ut, ut_dtrig *p, UTFLOAT *in, UTFLOAT *out)
{
    if(*in == 1.0){
        p->running = 1.0;
        p->pos = 0;
        p->counter = p->delay * ut->sr;
    } 
    if((p->pos < p->ft->size) && p->running){
        if(p->counter == 0){
            p->counter = (uint32_t)(p->scale * p->ft->tbl[p->pos] * ut->sr - 1);
            *out = 1.0;
            p->pos++; 
            if(p->loop){
                p->pos %= p->ft->size;
            }
            return UT_OK;
        }else{
            *out = 0;
            p->counter--;
            return UT_OK;
        }
    }    
    *out = 0;
    return UT_NOT_OK;
}
