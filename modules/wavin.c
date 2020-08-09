#include <stdlib.h>
#include "utone.h"
#include "dr_wav.h"

#define WAVIN_BUFSIZE 1024

struct ut_wavin {
    UTFLOAT buf[WAVIN_BUFSIZE];
    int count;
    drwav wav;
    drwav_uint64 pos;
};

int ut_wavin_create(ut_wavin **p)
{
    *p = malloc(sizeof(ut_wavin));
    return UT_OK;
}

int ut_wavin_destroy(ut_wavin **p)
{
    drwav_uninit(&(*p)->wav);
    free(*p);
    return UT_OK;
}

int ut_wavin_init(ut_data *ut, ut_wavin *p, const char *filename)
{
    p->count = 0;
    p->pos = 0;
    drwav_init_file(&p->wav, filename);
    return UT_OK;
}

int ut_wavin_compute(ut_data *ut, ut_wavin *p, UTFLOAT *in, UTFLOAT *out)
{
    if(p->pos > p->wav.totalSampleCount) {
        *out = 0;
        return UT_OK;
    }
    if(p->count == 0) {
        drwav_read_f32(&p->wav, WAVIN_BUFSIZE, p->buf);
    }

    *out = p->buf[p->count];
    p->count = (p->count + 1) % WAVIN_BUFSIZE;
    p->pos++;
    return UT_OK;
}
