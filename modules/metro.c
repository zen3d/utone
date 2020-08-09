/*
 * Metro
 *
 * This code has been extracted from the Csound opcode "metro".
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): Gabriel Maldonado
 * Year: 2000
 * Location: Opcodes/metro.c
 *
 */

#include <stdlib.h>
#include "utone.h"

int ut_metro_create(ut_metro **p)
{
    *p = malloc(sizeof(ut_metro));
    return UT_OK;
}

int ut_metro_destroy(ut_metro **p)
{
    free(*p);
    return UT_OK;
}

int ut_metro_init(ut_data *ut, ut_metro *p)
{
    p->iphs = 0;
    p->freq= 2.0;
    UTFLOAT phs = p->iphs;
    int32_t  longphs = phs;
    if (phs >= 0.0){
      p->curphs = (UTFLOAT)phs - (UTFLOAT)longphs;
    }
    p->flag=1;
    p->onedsr = 1.0 / ut->sr;
    return UT_OK;
}

int ut_metro_compute(ut_data *ut, ut_metro *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT phs= p->curphs;
    if (phs == 0.0 && p->flag){
        *out = 1.0;
        p->flag = 0;
    }else if ((phs += p->freq * p->onedsr) >= 1.0){
        *out = 1.0;
        phs -= 1.0;
        p->flag = 0;
    }else{
        *out = 0.0;
    }
    p->curphs = phs;
    return UT_OK;
}
