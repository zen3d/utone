#include <stdlib.h>
#include "utone.h"

int ut_progress_create(ut_progress **p)
{
    *p = malloc(sizeof(ut_progress));
    return UT_OK;
}

int ut_progress_destroy(ut_progress **p)
{
    free(*p);
    return UT_OK;
}

int ut_progress_init(ut_data *ut, ut_progress *p)
{
    p->nbars = 40;
    p->skip = 1000;
    p->counter = 0;
    p->len = (uint32_t) ut->len;
    return UT_OK;
}

int ut_progress_compute(ut_data *ut, ut_progress *p, UTFLOAT *in, UTFLOAT *out)
{
    if(p->counter == 0 || ut->pos == p->len - 1) {
        int n;
        UTFLOAT slope = 1.0 / p->nbars;
        if(ut->pos == 0) fprintf(stderr, "\e[?25l");
        UTFLOAT percent = ((UTFLOAT)ut->pos / p->len);
        fprintf(stderr, "[");
        for(n = 0; n < p->nbars; n++) {
            if(n * slope <= percent) {
                fprintf(stderr, "#");
            }else {
                fprintf(stderr, " ");
            }
        }
        fprintf(stderr, "] %.2f%%\t\r", 100 * percent);

    }
    if(ut->pos == p->len - 1) fprintf(stderr, "\n\e[?25h");
    fflush(stderr);
    p->counter++;
    p->counter %= p->skip;
    return UT_OK;
}
