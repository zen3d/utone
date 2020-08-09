#include <stdlib.h>
#include <string.h>
#include "utone.h"
#include "sndfile.h"

struct ut_diskin {
    SNDFILE *file;
    SF_INFO info;
    UTFLOAT buffer[1024];
    int bufpos;
    int loaded;
    int count;
};

int ut_diskin_create(ut_diskin **p)
{
    *p = malloc(sizeof(ut_diskin));
    return UT_OK;
}

int ut_diskin_destroy(ut_diskin **p)
{
    ut_diskin *pp = *p;
    if(pp->loaded) sf_close(pp->file);
    free(*p);
    return UT_OK;
}

int ut_diskin_init(ut_data *ut, ut_diskin *p, const char *filename)
{
    p->info.format = 0;
    memset(&p->info, 0, sizeof(SF_INFO));
    p->file = sf_open(filename, SFM_READ, &p->info);
    p->loaded = 0;
    p->bufpos = 0;

    if(p->file == NULL) {
        fprintf(stderr, "Error: could not open file \"%s\"\n", filename);
        exit(1);
    }

    if(p->info.channels != 1) {
        fprintf(stderr, "Warning: file \"%s\" has %d channels," 
                "when it is expecting only 1\n", filename, p->info.channels);
    }

    p->loaded = 1;

    if(p->info.frames < 1024) {
        p->count = p->info.frames;
    } else {
        p->count = 1024;
    }
    memset(p->buffer, 0, sizeof(UTFLOAT) * 1024);
    return UT_OK;
}

int ut_diskin_compute(ut_data *ut, ut_diskin *p, UTFLOAT *in, UTFLOAT *out)
{
    if(p->bufpos == 0 && p->loaded && p->count > 0) {
#ifdef USE_DOUBLE
        p->count = sf_read_double(p->file, p->buffer, p->count);
#else
        p->count = sf_read_float(p->file, p->buffer, p->count);
#endif
    } 

    if(p->count <= 0) {
        *out = 0;
        return UT_OK;
    }

    *out = p->buffer[p->bufpos++];
    p->bufpos %= 1024; 
    return UT_OK;
}
