#include <stdlib.h>
#include "utone.h"
#include "dr_wav.h"

#define WAVOUT_BUFSIZE 1024

struct ut_wavout {
    drwav *wav;
    drwav_data_format format;
    UTFLOAT buf[WAVOUT_BUFSIZE];
    int count;
};

int ut_wavout_create(ut_wavout **p)
{
    *p = malloc(sizeof(ut_wavout));
    return UT_OK;
}

int ut_wavout_destroy(ut_wavout **p)
{
    /* write any remaining samples */
    if((*p)->count != 0) {
        drwav_write((*p)->wav, (*p)->count, (*p)->buf);
    }
    drwav_close((*p)->wav);
    free(*p);
    return UT_OK;
}

int ut_wavout_init(ut_data *ut, ut_wavout *p, const char *filename)
{
    p->count = 0;
    p->format.container = drwav_container_riff;
    p->format.format = DR_WAVE_FORMAT_IEEE_FLOAT;
    p->format.channels = 1;
    p->format.sampleRate = ut->sr;
    p->format.bitsPerSample = 32;
    p->wav = drwav_open_file_write(filename, &p->format);
    return UT_OK;
}

int ut_wavout_compute(ut_data *ut, ut_wavout *p, UTFLOAT *in, UTFLOAT *out)
{
    *out = *in;
    if(p->count == WAVOUT_BUFSIZE) {
        drwav_write(p->wav, WAVOUT_BUFSIZE, p->buf);
        p->count = 0;
    }
    p->buf[p->count] = *in;
    p->count++;
    return UT_OK;
}
