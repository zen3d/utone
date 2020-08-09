/*
 * Fold
 *
 * This code has been extracted from the Csound opcode "fold".
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): John FFitch, Gabriel Maldonado
 * Year: 1998
 * Location: OOps/ugens2.c
 *
 */

#include <stdlib.h>
#include "utone.h"

int ut_fold_create(ut_fold **p)
{
    *p = malloc(sizeof(ut_fold));
    return UT_OK;
}

int ut_fold_destroy(ut_fold **p)
{
    free(*p);
    return UT_OK;
}

int ut_fold_init(ut_data *ut, ut_fold *p)
{
    p->incr = 1000;
    p->sample_index = 0;
    p->index = 0.0;
    p->value = 0.0; 
    return UT_OK;
}

int ut_fold_compute(ut_data *ut, ut_fold *p, UTFLOAT *in, UTFLOAT *out)
{
    UTFLOAT index = p->index;
    int32_t sample_index = p->sample_index;
    UTFLOAT value = p->value;
    if (index < (UTFLOAT)sample_index) {
        index += p->incr;
        *out = value = *in;
    } else {
        *out = value;
    }
    sample_index++;
    p->index = index;
    p->sample_index = sample_index;
    p->value = value;
    return UT_OK;
}
