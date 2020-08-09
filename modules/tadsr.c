/*
 * TADSR
 * 
 * This module uses modified code from Perry Cook's ADSR STK module.
 * 
 */

#include <stdlib.h>
#include <math.h>
#include "utone.h"

enum{ ATTACK, DECAY, SUSTAIN, RELEASE, CLEAR, KEY_ON, KEY_OFF };

static void make_Envelope(ut_tadsr *e)
{
    e->target = 0.0;
    e->value = 0.0;
    e->rate = 0.001;
    e->state = 1;
}

static void make_ADSR(ut_tadsr *a)
{
    make_Envelope(a);
    a->target = 0.0;
    a->value = 0.0;
    a->attackRate = 0.001;
    a->decayRate = 0.001;
    a->sustainLevel = 0.0;
    a->releaseRate = 0.01;
    a->state = CLEAR;
}

static void ADSR_keyOn(ut_tadsr *a)
{
    a->target = 1.0;
    a->rate = a->attackRate;
    a->state = ATTACK;
}

static void ADSR_keyOff(ut_tadsr *a)
{
    a->target = 0.0;
    a->rate = a->releaseRate;
    a->state = RELEASE;
}

static void ADSR_setSustainLevel(ut_data *ut, ut_tadsr *a, UTFLOAT aLevel)
{
   a->sustainLevel = aLevel;
}

static void ADSR_setAttackTime(ut_data *ut, ut_tadsr *a, UTFLOAT aTime)
{
    a->attackRate = 1.0 / (aTime * ut->sr);
}

static void ADSR_setDecayTime(ut_data *ut, ut_tadsr *a, UTFLOAT aTime)
{
    a->decayRate = 1.0 / (aTime * ut->sr);
}

static void ADSR_setReleaseTime(ut_data *ut, ut_tadsr *a, UTFLOAT aTime)
{
    a->releaseRate = 1.0 / (aTime * ut->sr);
}

static void ADSR_setAllTimes(ut_data *ut, ut_tadsr *a, UTFLOAT attTime, UTFLOAT decTime,
                      UTFLOAT susLevel, UTFLOAT relTime)
{
    ADSR_setAttackTime(ut, a, attTime);
    ADSR_setDecayTime(ut, a, decTime);
    ADSR_setSustainLevel(ut, a, susLevel);
    ADSR_setReleaseTime(ut, a, relTime);
}

static UTFLOAT ADSR_tick(ut_tadsr *a)
{
    UTFLOAT out = 0;
    if (a->state == ATTACK) {
        a->value += a->rate;
        if (a->value >= a->target) {
            a->value = a->target;
            a->rate = a->decayRate;
            a->target = a->sustainLevel;
            a->state = DECAY;
        }
        out = a->value;
    } else if (a->state == DECAY) {
        a->value -= a->decayRate;
        out = a->value;
        if (a->value <= a->sustainLevel) {
            a->value = a->sustainLevel;
            out = a->sustainLevel;
            a->rate = 0.0;
            a->state = SUSTAIN;
        }
    } else if (a->state == RELEASE)  {
        a->value -= a->releaseRate;
        if (a->value <= 0.0) {
            a->value = 0.0;
            a->state = CLEAR;
        }
        out = a->value;
    } else if (a->state == SUSTAIN)  {
        out = a->sustainLevel;
    }
    return out;
}

int ut_tadsr_create(ut_tadsr **p)
{
    *p = malloc(sizeof(ut_tadsr));
    return UT_OK;
}

int ut_tadsr_destroy(ut_tadsr **p)
{
    free(*p);
    return UT_OK;
}

int ut_tadsr_init(ut_data *ut, ut_tadsr *p)
{
    make_ADSR(p);
    p->atk = 0.5;
    p->dec = 0.5;
    p->sus = 0.0;
    p->rel = 0.5;
    p->mode = KEY_OFF;
    return UT_OK;
}

int ut_tadsr_compute(ut_data *ut, ut_tadsr *p, UTFLOAT *trig, UTFLOAT *out)
{
    if(*trig != 0) {

        if(*trig == 2) {
            ADSR_keyOff(p);
            p->mode = KEY_OFF;
        }else if(p->mode == KEY_OFF) {
            ADSR_setAllTimes(ut, p, p->atk, p->dec, p->sus, p->rel);
            ADSR_keyOn(p);
            p->mode = KEY_ON;
        } else {
            ADSR_keyOff(p);
            p->mode = KEY_OFF;
        }
    }
    *out = ADSR_tick(p);
    return UT_OK;
}
