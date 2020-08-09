#include <stdint.h>
#include <stdio.h>

#define UT_BUFSIZE 4096
#ifndef UTFLOAT
#define UTFLOAT float
#endif 
#define UT_OK 1
#define UT_NOT_OK 0

#define UT_RANDMAX 2147483648

typedef unsigned long ut_frame;

typedef struct ut_auxdata {
    size_t size;
    void *ptr;
} ut_auxdata;

typedef struct ut_data { 
    UTFLOAT *out;
    int sr;
    int nchan;
    unsigned long len;
    unsigned long pos;
    char filename[200];
    uint32_t rand;
} ut_data; 

typedef struct {
    char state;
    UTFLOAT val;
} ut_param;

int ut_auxdata_alloc(ut_auxdata *aux, size_t size);
int ut_auxdata_free(ut_auxdata *aux);

int ut_create(ut_data **utp);
int ut_createn(ut_data **utp, int nchan);

int ut_destroy(ut_data **utp);
int ut_process(ut_data *ut, void *ud, void (*callback)(ut_data *, void *));
int ut_process_raw(ut_data *ut, void *ud, void (*callback)(ut_data *, void *));
int ut_process_plot(ut_data *ut, void *ud, void (*callback)(ut_data *, void *));
int ut_process_spa(ut_data *ut, void *ud, void (*callback)(ut_data *, void *));

UTFLOAT ut_midi2cps(UTFLOAT nn);

int ut_set(ut_param *p, UTFLOAT val);

int ut_out(ut_data *ut, uint32_t chan, UTFLOAT val);

uint32_t ut_rand(ut_data *ut);
void ut_srand(ut_data *ut, uint32_t val);


typedef struct {
    UTFLOAT *utbl;
    int16_t *BRLow;
    int16_t *BRLowCpx;
} ut_fft;

void ut_fft_init(ut_fft *fft, int M);
void ut_fftr(ut_fft *fft, UTFLOAT *buf, int FFTsize);
void ut_fft_cpx(ut_fft *fft, UTFLOAT *buf, int FFTsize);
void ut_ifftr(ut_fft *fft, UTFLOAT *buf, int FFTsize);
void ut_fft_destroy(ut_fft *fft);
#ifndef kiss_fft_scalar
#define kiss_fft_scalar UTFLOAT
#endif
typedef struct {
    kiss_fft_scalar r;
    kiss_fft_scalar i;
}kiss_fft_cpx;

typedef struct kiss_fft_state* kiss_fft_cfg;
typedef struct kiss_fftr_state* kiss_fftr_cfg;

/* SPA: Soundpipe Audio */

enum { UTA_READ, UTA_WRITE, UTA_NULL };

typedef struct {
    char magic;
    char nchan;
    uint16_t sr;
    uint32_t len;
} uta_header;

typedef struct {
    uta_header header;
    size_t offset;
    int mode;
    FILE *fp;
    uint32_t pos;
} ut_audio;

