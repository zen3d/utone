#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "utone.h"

#define CHECK_NULL_FILE(fp) if(fp == NULL) return UT_NOT_OK

int uta_open(ut_data *ut, ut_audio *uta, const char *name, int mode)
{
    uta->mode = UTA_NULL;
    uta_header *header = &uta->header;
    uta->offset = sizeof(uta_header);
    if(mode == UTA_READ) {
        uta->fp = fopen(name, "rb");
        CHECK_NULL_FILE(uta->fp);
        fread(header, uta->offset, 1, uta->fp);
    } else if(mode == UTA_WRITE) {
        uta->fp = fopen(name, "wb");
        CHECK_NULL_FILE(uta->fp);
        header->magic = 100;
        header->nchan = ut->nchan;
        header->len = ut->len;
        header->sr = ut->sr;
        fwrite(header, uta->offset, 1, uta->fp);
    } else {
        return UT_NOT_OK;
    }

    uta->mode = mode;

    return UT_OK;
}

size_t uta_write_buf(ut_data *ut, ut_audio *uta, UTFLOAT *buf, uint32_t size)
{
    if(uta->mode != UTA_WRITE) {
        return 0;
    }
    return fwrite(buf, sizeof(UTFLOAT), size, uta->fp);
}

size_t uta_read_buf(ut_data *ut, ut_audio *uta, UTFLOAT *buf, uint32_t size)
{
    if(uta->mode != UTA_READ) {
        return 0;
    }
    return fread(buf, sizeof(UTFLOAT), size, uta->fp);
}

int uta_close(ut_audio *uta)
{
    if(uta->fp != NULL) fclose(uta->fp);
    return UT_OK;
}

int ut_process_uta(ut_data *ut, void *ud, void (*callback)(ut_data *, void *))
{
    ut_audio uta;
    if(uta_open(ut, &uta, ut->filename, UTA_WRITE) == UT_NOT_OK) {
        fprintf(stderr, "Error: could not open file %s.\n", ut->filename);    
    }
    while(ut->len > 0) {
        callback(ut, ud);
        uta_write_buf(ut, &uta, ut->out, ut->nchan);
        ut->len--;
        ut->pos++;
    }
    uta_close(&uta);
    return UT_OK;
}

int ut_ftbl_loaduta(ut_data *ut, ut_ftbl **ft, const char *filename)
{
    *ft = malloc(sizeof(ut_ftbl));
    ut_ftbl *ftp = *ft;

    ut_audio uta;

    uta_open(ut, &uta, filename, UTA_READ);

    size_t size = uta.header.len;

    ftp->tbl = malloc(sizeof(UTFLOAT) * (size + 1));
    ut_ftbl_init(ut, ftp, size);

    uta_read_buf(ut, &uta, ftp->tbl, ftp->size);
    uta_close(&uta);
    return UT_OK;
}

