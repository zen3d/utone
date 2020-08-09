#include <stdlib.h>
#include "utone.h"

int ut_tenv_create(ut_tenv **p)
{
    *p = malloc(sizeof(ut_tenv));
    ut_tenv *pp = *p;
    ut_tevent_create(&pp->te);
    return UT_OK;
}

int ut_tenv_destroy(ut_tenv **p)
{
    ut_tenv *pp = *p;
    ut_tevent_destroy(&pp->te);
    free(*p);
    return UT_OK;
}

static void ut_tenv_reinit(void *ud)
{
    ut_tenv *env = ud;
    env->pos = 0;
    env->atk_end = env->sr * env->atk;
    env->rel_start = env->sr * (env->atk + env->hold);
    env->atk_slp = 1.0 / env->atk_end;
    env->rel_slp = -1.0 / (env->sr * env->rel);
    env->totaldur = env->sr * (env->atk + env->hold + env->rel);
}

static void ut_tenv_comp(void *ud, UTFLOAT *out)
{
    ut_tenv *env = ud;
    UTFLOAT sig = 0;
    uint32_t pos = env->pos;
    *out = 0.0;
    if(pos < env->atk_end){
        sig = env->last + env->atk_slp;
    }else if (pos < env->rel_start){
        sig = 1.0;
    }else if (pos < env->totaldur){
        sig = env->last + env->rel_slp;
    }else{
        sig = 0.0;
    }
    sig = (sig > 1.0) ? 1.0 : sig;
    sig = (sig < 0.0) ? 0.0 : sig;

    /* Internal input signal mode */
    if(env->sigmode) {
        *out = env->input * sig;
    } else {
        *out = sig;
    }


    env->pos++;
    env->last = sig;
}

int ut_tenv_init(ut_data *ut, ut_tenv *p)
{
    p->pos = 0;
    p->last = 0;
    p->atk = 0.1;
    p->hold = 0.3;
    p->rel = 0.2;
    p->sigmode = 0;
    p->input = 0;

    p->sr = ut->sr;
    p->atk_end = p->sr * p->atk;
    p->rel_start = p->sr * (p->atk + p->hold);
    p->atk_slp = 1.0 / p->atk_end;
    p->rel_slp = -1.0 / (p->sr * p->rel);
    p->totaldur = p->sr * (p->atk + p->hold + p->rel);
    ut_tevent_init(ut, p->te, ut_tenv_reinit, ut_tenv_comp, p);
    return UT_OK;
}

int ut_tenv_compute(ut_data *ut, ut_tenv *p, UTFLOAT *in, UTFLOAT *out)
{
    ut_tevent_compute(ut, p->te, in, out);
    return UT_OK;
}
