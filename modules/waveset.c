/*
 * Waveset
 *
 * This code has been extracted from the Csound opcode "waveset".
 * It has been modified to work as a Soundpipe module.
 *
 * Original Author(s): Trevor Wishart, John ffitch
 * Year: 2001
 * Location: Opcodes/pitch.c
 *
 */

#include <stdlib.h>
#include "utone.h"

int ut_waveset_create(ut_waveset **p)
{
    *p = malloc(sizeof(ut_waveset));
    return UT_OK;
}

int ut_waveset_destroy(ut_waveset **p)
{
    ut_waveset *pp = *p;
    ut_auxdata_free(&pp->auxch);
    free(*p);
    return UT_OK;
}

int ut_waveset_init(ut_data *ut, ut_waveset *p, UTFLOAT ilen)
{
    p->length = 1 + (ut->sr * ilen);

    ut_auxdata_alloc(&p->auxch, p->length * sizeof(UTFLOAT));
    p->cnt = 1;
    p->start = 0;
    p->current = 0;
    p->end = 0;
    p->direction = 1;
    p->lastsamp = 1.0;
    p->noinsert = 0;
    return UT_OK;
}

int ut_waveset_compute(ut_data *ut, ut_waveset *p, UTFLOAT *in, UTFLOAT *out)
{
    int index = p->end;
    UTFLOAT *insert = (UTFLOAT*)(p->auxch.ptr) + index;

    if (p->noinsert) goto output;
    *insert++ = *in;
    if (++index ==  p->start) {
        p->noinsert = 1;
    }
    if (index==p->length) {  
        index = 0;
        insert = (UTFLOAT*)(p->auxch.ptr);
    }

    output:

    p->end = index;
    index = p->current;
    insert = (UTFLOAT*)(p->auxch.ptr) + index;
    UTFLOAT samp = *insert++;
    index++;

    if (index==p->length) {
        index = 0;
        insert = (UTFLOAT*)(p->auxch.ptr);
        p->noinsert = 0;
    }

    if (samp != 0.0 && p->lastsamp*samp < 0.0) {
        if (p->direction == 1) {
            p->direction = -1;
        } else {
            p->direction = 1;
            if (++p->cnt > p->rep) {
                p->cnt = 1;
                p->start = index;
                p->noinsert = 0;
            } else { index = p->start;
                insert = (UTFLOAT*)(p->auxch.ptr) + index;
            }
        }
    }

    if (samp != 0.0) p->lastsamp = samp;
    *out = samp;
    p->current = index;

    return UT_OK;
}
