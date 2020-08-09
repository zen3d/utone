#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef NO_LIBSNDFILE
#include <sndfile.h>
#endif
#include "utone.h"

#ifndef M_PI
#define M_PI		3.14159265358979323846	/* pi */
#endif

#define tpd360  0.0174532925199433

/* initialize constants in ftable */
int ut_ftbl_init(ut_data *ut, ut_ftbl *ft, size_t size)
{
    ft->size = size;
    ft->sicvt = 1.0 * UT_FT_MAXLEN / ut->sr;
    ft->lobits = log2(UT_FT_MAXLEN / size);
    ft->lomask = (1<<ft->lobits) - 1;
    ft->lodiv = 1.0 / (1<<ft->lobits);
    ft->del = 1;
    return UT_OK;
}

int ut_ftbl_create(ut_data *ut, ut_ftbl **ft, size_t size)
{
    *ft = malloc(sizeof(ut_ftbl));
    ut_ftbl *ftp = *ft;
    ftp->tbl = malloc(sizeof(UTFLOAT) * (size + 1));
    memset(ftp->tbl, 0, sizeof(UTFLOAT) * (size + 1));
   
    ut_ftbl_init(ut, ftp, size);
    return UT_OK;
}

int ut_ftbl_bind(ut_data *ut, ut_ftbl **ft, UTFLOAT *tbl, size_t size)
{
    *ft = malloc(sizeof(ut_ftbl));
    ut_ftbl *ftp = *ft;
    ftp->tbl = tbl;
    ut_ftbl_init(ut, ftp, size);
    ftp->del = 0;
    return UT_OK;
}

int ut_ftbl_destroy(ut_ftbl **ft)
{
    ut_ftbl *ftp = *ft;
    if(ftp->del) free(ftp->tbl);
    free(*ft);
    return UT_OK;
}

/* TODO: handle spaces at beginning of string */
static char * tokenize(char **next, int *size)
{
    if(*size <= 0) return NULL;
    char *token = *next;
    char *str = *next;

    char *peak = str + 1;

    while((*size)--) {
        if(*str == ' ') {
            *str = 0;
            if(*peak != ' ') break;
        }
        str = str + 1;
        peak = str + 1;
    }
    *next = peak;
    return token;
}

int ut_gen_vals(ut_data *ut, ut_ftbl *ft, const char *string)
{
    int size = strlen(string);
    char *str = malloc(sizeof(char) * size + 1);
    strcpy(str, string);
    char *out; 
    char *ptr = str;
    int j = 0;
    while(size > 0) {
        out = tokenize(&str, &size);
        if(ft->size < j + 1){
            ft->tbl = realloc(ft->tbl, sizeof(UTFLOAT) * (ft->size + 2));
            /* zero out new tables */
            ft->tbl[ft->size] = 0;
            ft->tbl[ft->size + 1] = 0;
            ft->size++;
        }
        ft->tbl[j] = atof(out);
        j++;
    }
  
    ut_ftbl_init(ut, ft, ft->size);
    free(ptr); 
    return UT_OK;
}

int ut_gen_sine(ut_data *ut, ut_ftbl *ft)
{
    unsigned long i;
    UTFLOAT step = 2 * M_PI / ft->size;
    for(i = 0; i < ft->size; i++){
        ft->tbl[i] = sin(i * step);
    }
    return UT_OK;
}

#ifndef NO_LIBSNDFILE
/*TODO: add error checking, make tests */
int ut_gen_file(ut_data *ut, ut_ftbl *ft, const char *filename)
{
    SF_INFO info;
    memset(&info, 0, sizeof(SF_INFO));
    info.format = 0;
    SNDFILE *snd = sf_open(filename, SFM_READ, &info);
#ifdef USE_DOUBLE
    sf_readf_double(snd, ft->tbl, ft->size);
#else
    sf_readf_float(snd, ft->tbl, ft->size);
#endif
    sf_close(snd);
    return UT_OK;
}

int ut_ftbl_loadfile(ut_data *ut, ut_ftbl **ft, const char *filename)
{
    *ft = malloc(sizeof(ut_ftbl));
    ut_ftbl *ftp = *ft;
    SF_INFO info;
    memset(&info, 0, sizeof(SF_INFO));
    info.format = 0;
    SNDFILE *snd = sf_open(filename, SFM_READ, &info);
    if(snd == NULL) {
        return UT_NOT_OK;
    }
    size_t size = info.frames * info.channels;

    ftp->tbl = malloc(sizeof(UTFLOAT) * (size + 1));

    ut_ftbl_init(ut, ftp, size);

#ifdef USE_DOUBLE
    sf_readf_double(snd, ftp->tbl, ftp->size);
#else
    sf_readf_float(snd, ftp->tbl, ftp->size);
#endif
    sf_close(snd);
    return UT_OK;
}
#endif

/* port of GEN10 from Csound */
int ut_gen_sinesum(ut_data *ut, ut_ftbl *ft, const char *argstring)
{
    ut_ftbl *args;
    ut_ftbl_create(ut, &args, 1);
    ut_gen_vals(ut, args, argstring);

    int32_t phs;
    UTFLOAT amp;
    int32_t flen = (int32_t)ft->size;
    UTFLOAT tpdlen = 2.0 * M_PI / (UTFLOAT) flen;

    int32_t i, n;

    for(i = (int32_t)args->size; i > 0; i--){
        amp = args->tbl[args->size - i];
        if(amp != 0) {
            for(phs = 0, n = 0; n < ft->size; n++){
                ft->tbl[n] += sin(phs * tpdlen) * amp;
                phs += i;
                phs %= flen;
            }
        }
    }
    ut_ftbl_destroy(&args);
    return UT_OK;
}

int ut_gen_line(ut_data *ut, ut_ftbl *ft, const char *argstring)
{
    uint16_t i, n = 0, seglen;
    UTFLOAT incr, amp = 0;
    UTFLOAT x1, x2, y1, y2;
    ut_ftbl *args;
    ut_ftbl_create(ut, &args, 1);
    ut_gen_vals(ut, args, argstring);

    if((args->size % 2) == 1 || args->size == 1) {
        fprintf(stderr, "Error: not enough arguments for gen_line.\n");
        ut_ftbl_destroy(&args);
        return UT_NOT_OK;
    } else if(args->size == 2) {
        for(i = 0; i < ft->size; i++) {
            ft->tbl[i] = args->tbl[1];
        }
        return UT_OK;
    }

    x1 = args->tbl[0];
    y1 = args->tbl[1];
    for(i = 2; i < args->size; i += 2) {
        x2 = args->tbl[i];
        y2 = args->tbl[i + 1];

        if(x2 < x1) {
            fprintf(stderr, "Error: x coordiates must be sequential!\n");
            break;
        }

        seglen = (x2 - x1);
        incr = (UTFLOAT)(y2 - y1) / (seglen - 1);
        amp = y1;

        while(seglen != 0){
            if(n < ft->size) {
                ft->tbl[n] = amp;
                amp += incr;
                seglen--;
                n++;
            } else {
                break;
            }
        }
        y1 = y2;
        x1 = x2;
    }

    ut_ftbl_destroy(&args);
    return UT_OK;
}

int ut_gen_xline(ut_data *ut, ut_ftbl *ft, const char *argstring)
{
    uint16_t i, n = 0, seglen;
    UTFLOAT mult, amp = 0;
    UTFLOAT x1, x2, y1, y2;
    ut_ftbl *args;
    ut_ftbl_create(ut, &args, 1);
    ut_gen_vals(ut, args, argstring);

    if((args->size % 2) == 1 || args->size == 1) {
        fprintf(stderr, "Error: not enough arguments for gen_line.\n");
        ut_ftbl_destroy(&args);
        return UT_NOT_OK;
    } else if(args->size == 2) {
        for(i = 0; i < ft->size; i++) {
            ft->tbl[i] = args->tbl[1];
        }
        return UT_OK;
    }

    x1 = args->tbl[0];
    y1 = args->tbl[1];
    for(i = 2; i < args->size; i += 2) {
        x2 = args->tbl[i];
        y2 = args->tbl[i + 1];

        if(x2 < x1) {
            fprintf(stderr, "Error: x coordiates must be sequential!\n");
            break;
        }

        if(y1 == 0) {
            y1 = 0.000001;
        }

        if(y2 == 0) {
            y2 = 0.000001;
        }

        seglen = (uint32_t)(x2 - x1);
        mult = (y2 / y1);
        mult = pow(mult, (UTFLOAT)1.0 / seglen);
        amp = y1;

        while(seglen != 0){
            if(n < ft->size) {
                ft->tbl[n] = amp;
                amp *= mult;
                seglen--;
                n++;
            } else {
                break;
            }
        }
        y1 = y2;
        x1 = x2;
    }

    ut_ftbl_destroy(&args);
    return UT_OK;

}


static UTFLOAT gaussrand(ut_randmt *p, UTFLOAT scale)
{
    int64_t r1 = -((int64_t)0xFFFFFFFFU * 6);
    int n = 12;
    UTFLOAT x;

    do {
      r1 += (int64_t)ut_randmt_compute(p);
    } while (--n);

    x = (UTFLOAT)r1;
    return (UTFLOAT)(x * ((UTFLOAT)scale * (1.0 / (3.83 * 4294967295.03125))));
}

int ut_gen_gauss(ut_data *ut, ut_ftbl *ft, UTFLOAT scale, uint32_t seed)
{
    int n;

    ut_randmt rand;

    ut_randmt_seed(&rand, NULL, seed);

    for(n = 0; n < ft->size; n++) {
        ft->tbl[n] = gaussrand(&rand, scale);
    }

    return UT_OK;
}

/* based off of GEN 19 */
int ut_gen_composite(ut_data *ut, ut_ftbl *ft, const char *argstring)
{
    UTFLOAT phs, inc, amp, dc, tpdlen = 2 * M_PI/ (UTFLOAT) ft->size;
    int i, n;
    
    ut_ftbl *args;
    ut_ftbl_create(ut, &args, 1);
    ut_gen_vals(ut, args, argstring);

    for(n = 0; n < args->size; n += 4) {
        inc = args->tbl[n] * tpdlen;
        amp = args->tbl[n + 1];
        phs = args->tbl[n + 2] * tpd360;
        dc = args->tbl[n + 3];

        for (i = 0; i <ft->size ; i++) {
            ft->tbl[i] += (UTFLOAT) (sin(phs) * amp + dc);
            if ((phs += inc) >= 2 * M_PI) phs -= 2 * M_PI;
        }
    }

    ut_ftbl_destroy(&args);
    return UT_OK;
}

int ut_gen_rand(ut_data *ut, ut_ftbl *ft, const char *argstring)
{
    ut_ftbl *args;
    ut_ftbl_create(ut, &args, 1);
    ut_gen_vals(ut, args, argstring);
    int n, pos = 0, i, size = 0;

    for(n = 0; n < args->size; n += 2) {
        size = round(ft->size * args->tbl[n + 1]);
        for(i = 0; i < size; i++) {
            if(pos < ft->size) {
                ft->tbl[pos] = args->tbl[n];
                pos++;
            }
        }
    }
    if(pos <= ft->size) {
        ft->size = pos;
    }
    ut_ftbl_destroy(&args);
    return UT_OK;
}

int ut_gen_triangle(ut_data *ut, ut_ftbl *ft)
{
    unsigned int i;
    unsigned int counter;
    UTFLOAT incr;
    int step;

    incr = 1.0f / (UTFLOAT)ft->size;
    incr *= 2;

    step = 1;

    counter = 0;

    for(i = 0; i < ft->size; i++) {
        if(i == ft->size / 2) {
            step = -1;
        }
        ft->tbl[i] = (2.f*(counter * incr) - 1.f);

        counter += step;
    }

    return UT_OK;
}
