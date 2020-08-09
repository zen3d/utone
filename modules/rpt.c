#include <stdlib.h>
#include "utone.h"

static int ut_rpt_set(ut_rpt *p, UTFLOAT bpm, int div, int rep);

int ut_rpt_create(ut_rpt **p)
{
    *p = malloc(sizeof(ut_rpt));
    return UT_OK;
}

int ut_rpt_destroy(ut_rpt **p)
{
    ut_rpt *pp = *p;
    ut_auxdata_free(&pp->aux);
    free(*p);
    return UT_OK;
}

int ut_rpt_init(ut_data *ut, ut_rpt *p, UTFLOAT maxdur)
{
    ut_auxdata_alloc(&p->aux, sizeof(UTFLOAT) * (uint32_t)maxdur * ut->sr);
    p->playpos = 0;
    p->bufpos = 0;
    p->running = 0;
    p->reps = 4;
    p->count = p->reps;
    p->size = (int)p->aux.size;
    p->sr = ut->sr;
    p->bpm = 130;
    p->div = 4;
    p->rep = 4;
    p->rc = UT_OK;
    return UT_OK;
}

int ut_rpt_compute(ut_data *ut, ut_rpt *p, UTFLOAT *trig,
        UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT *buf = (UTFLOAT *)p->aux.ptr;
    if(p->rc == UT_NOT_OK) {
        *out = 0;
        return UT_NOT_OK;
    }
    if(*trig > 0){
        p->rc = ut_rpt_set(p, p->bpm, p->div, p->rep);
        p->running = 1;
        p->playpos = 0;
        p->bufpos = 0;
        p->count = p->reps + 1;
    }
    if(p->bufpos * sizeof(UTFLOAT) < p->aux.size){
        p->rc = ut_rpt_set(p, p->bpm, p->div, p->rep);
        buf[p->bufpos] = *in;
        p->bufpos++;
    }else{
        p->running = 0;
    }
    if(p->running && p->count > 0){
        if(p->playpos == 0){
            p->count--;
        }
        *out = buf[p->playpos];
        p->playpos = (p->playpos + 1) % p->size;
    }else{
        *out = *in;
    }
    return UT_OK;
}

static int ut_rpt_set(ut_rpt *p, UTFLOAT bpm, int div, int rep)
{
    uint32_t size = (p->sr * (60.0 / bpm)) / (UTFLOAT) div;
    p->reps = rep;
    if(size * sizeof(UTFLOAT) > p->aux.size){
        fprintf(stderr, "Error: not enough memory allocated for buffer.\n");
        return UT_NOT_OK;
    }else if(size <= 0){
        fprintf(stderr, "Error: Size cannot be zero.\n");
        return UT_NOT_OK;
    }else{
        p->size = size;
    }
    return UT_OK;
}
