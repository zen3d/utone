#include <stdlib.h>
#include "utone.h"

int ut_tseq_create(ut_tseq **p)
{
    *p = malloc(sizeof(ut_tseq));
    return UT_OK;
}

int ut_tseq_destroy(ut_tseq **p)
{
    free(*p);
    return UT_OK;
}

int ut_tseq_init(ut_data *ut, ut_tseq *p, ut_ftbl *ft)
{
    p->ft = ft;
    p->pos = -1;
    p->val = 0;
    p->shuf = 0;
    return UT_OK;
}

int ut_tseq_compute(ut_data *ut, ut_tseq *p, UTFLOAT *trig, UTFLOAT *val)
{    
    if(*trig != 0){
        if(p->shuf) {
            p->pos = ut_rand(ut) % p->ft->size;
        } else {
            p->pos = (p->pos + 1) % p->ft->size;
        }
        p->val = p->ft->tbl[p->pos];
    }
    *val = p->val;
    return UT_OK;
}
