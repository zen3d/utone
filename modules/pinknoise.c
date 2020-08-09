/*
 * Pinknoise
 *
 * This code has been extracted the pink noise synthesizer from Protrekkr
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): McCartney, Juan Antonio Arguelles
 * Location: release/distrib/replay/lib/replay.cpp
 *
 */
#include <stdlib.h>
#include <math.h>
#include "utone.h"


static uint32_t ctz[64] =
{
    6, 0, 1, 0, 2, 0, 1, 0,
    3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0,
    3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0,
    3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0,
    3, 0, 1, 0, 2, 0, 1, 0,
};

int ut_pinknoise_create(ut_pinknoise **p)
{
    *p = malloc(sizeof(ut_pinknoise));
    return UT_OK;
}

int ut_pinknoise_destroy(ut_pinknoise **p)
{
    free(*p);
    return UT_OK;
}

int ut_pinknoise_init(ut_data *ut, ut_pinknoise *p)
{
    int i;
    p->amp = 1.0;
    p->seed = ut_rand(ut);
    p->total = 0;
    p->counter = 0;
    for(i = 0; i < 7; i++) {
        p->dice[i] = 0;
    }
    return UT_OK;
}

int ut_pinknoise_compute(ut_data *ut, ut_pinknoise *p, UTFLOAT *in, UTFLOAT *out) 
{
    uint32_t k = ctz[p->counter & 63];
    p->prevrand = p->dice[k];
    p->seed = 1664525 * p->seed + 1013904223;
    p->newrand = p->seed >> 3;
    p->dice[k] = p->newrand;
    p->total += (p->newrand - p->prevrand);
    p->seed = 1103515245 * p->seed + 12345;
    p->newrand = p->seed >> 3;
    short tmp = (short) ((((p->total + p->newrand) * (1.0f / (3 << 29)) - 1) - .25f) * 16384.0f);
    
    *out = ((UTFLOAT) tmp / 32767) * p->amp;
    p->counter = (p->counter + 1) % 0xFFFFFFFF;
    return UT_OK;
}
