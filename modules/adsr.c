#include <stdlib.h>
#include <math.h>
#include "utone.h"

enum { CLEAR, ATTACK, DECAY, SUSTAIN, RELEASE };

int ut_adsr_create(ut_adsr **p)
{
    *p = malloc(sizeof(ut_adsr));
    return UT_OK;
}

int ut_adsr_destroy(ut_adsr **p)
{
    free(*p);
    return UT_OK;
}

int ut_adsr_init(ut_data *ut, ut_adsr *p)
{
    p->atk = 0.1;
    p->dec = 0.1;
    p->sus = 0.5;
    p->rel = 0.3;
    p->timer = 0;
    p->a = 0;
    p->b = 0;
    p->y = 0;
    p->x = 0;
    p->prev = 0;
    p->atk_time = p->atk * ut->sr;
    p->mode = CLEAR;
    return UT_OK;
}

static UTFLOAT tau2pole(ut_data *ut, ut_adsr *p, UTFLOAT tau)
{
    return exp(-1.0 / (tau * ut->sr));
}

static UTFLOAT adsr_filter(ut_data *ut, ut_adsr *p)
{
    p->y = p->b * p->x  + p->a * p->y;
    return p->y;
}

int ut_adsr_compute(ut_data *ut, ut_adsr *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT pole;
    if(p->prev < *in && p->mode != DECAY) {
        p->mode = ATTACK;
        p->timer = 0;
        /* quick fix: uncomment if broken */
        /* pole = tau2pole(ut, p, p->atk * 0.75); */
        /* p->atk_time = p->atk * ut->sr * 1.5; */
        pole = tau2pole(ut, p, p->atk * 0.6);
        p->atk_time = p->atk * ut->sr;
        p->a = pole;
        p->b = 1 - pole;
    } else if(p->prev > *in) {
        p->mode = RELEASE;
        pole = tau2pole(ut, p, p->rel);
        p->a = pole;
        p->b = 1 - pole;
    }

    p->x = *in;
    p->prev = *in;

    switch(p->mode) {
        case CLEAR:
            *out = 0;
            break;
        case ATTACK:
            p->timer++;
            *out = adsr_filter(ut, p);
            /* quick fix: uncomment if broken */
            /* if(p->timer > p->atk_time) { */
            if(*out > 0.99) {
                p->mode = DECAY;
                pole = tau2pole(ut, p, p->dec);
                p->a = pole;
                p->b = 1 - pole;
            }
            break;
        case DECAY:
        case RELEASE:
            p->x *= p->sus;
            *out = adsr_filter(ut, p);
        default:
            break;        
    }

    return UT_OK;
}
