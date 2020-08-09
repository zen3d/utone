#include <stdlib.h>
#include <string.h>
#include "utone.h"

int ut_tblrec_create(ut_tblrec **p)
{
    *p = malloc(sizeof(ut_tblrec));
    return UT_OK;
}

int ut_tblrec_destroy(ut_tblrec **p)
{
    free(*p);
    return UT_OK;
}

int ut_tblrec_init(ut_data *ut, ut_tblrec *p, ut_ftbl *ft)
{
    p->index = 0;
    p->record = 0;
    p->ft = ft;
    return UT_OK;
}

int ut_tblrec_compute(ut_data *ut, ut_tblrec *p, UTFLOAT *in, UTFLOAT *trig, UTFLOAT *out)
{
    if(*trig != 0) {
        if(p->record == 1) {
            p->record = 0;
        } else {
            p->record = 1;
            p->index = 0;
            memset(p->ft->tbl, 0, sizeof(UTFLOAT) * p->ft->size);
        }
    }

    if(p->record) {
        p->ft->tbl[p->index] = *in;
        p->index = (p->index + 1) % p->ft->size;
    }

    *out = *in;
    return UT_OK;
}
