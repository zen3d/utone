#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utone.h"
#include "md5.h"
#include "test.h"


int ut_test_create(ut_test **t, uint32_t bufsize)
{
    uint32_t i;
    *t = malloc(sizeof(ut_test));
    ut_test *tp = *t;

    UTFLOAT *buf = malloc(sizeof(UTFLOAT) * bufsize);
    for(i = 0; i < bufsize; i++) tp->buf = 0;

    tp->buf = buf;
    tp->size = bufsize;
    tp->pos = 0;
    md5_init(&tp->state);
    tp->md5string[32] = '\0';
    tp->md5 = tp->md5string;
    tp->mode = NORMAL;
    return UT_OK;
}

int ut_test_destroy(ut_test **t)
{
    ut_test *tp = *t;
    free(tp->buf);
    free(*t);
    return UT_OK;
}

int ut_test_add_sample(ut_test *t, UTFLOAT sample)
{
    if(t->pos < t->size) {
        t->buf[t->pos] = sample;
        t->pos++;
    }
    return UT_OK;
}

int ut_test_compare(ut_test *t, const char *md5hash)
{
    md5_append(&t->state, (const md5_byte_t *)t->buf, sizeof(UTFLOAT) * t->size);
    md5_finish(&t->state, t->digest);
    int i;
    char in[3], out[3];
    int fail = 0;
    for(i = 0; i < 16; i++) {
        in[0] = md5hash[2 * i];
        in[1] = md5hash[2 * i + 1];
        in[2] = '\0';
        sprintf(out, "%02x", t->digest[i]);
        t->md5string[2 * i] = out[0];
        t->md5string[2 * i + 1] = out[1];
        if(strcmp(in, out)) {
            fail = 1;
        }
    }

    if(fail) {
        return UT_NOT_OK;
    } else {
        return UT_OK;
    }
}

int ut_test_write_raw(ut_test *t, uint32_t index) 
{
    char fname[20];
    sprintf(fname, "%04d.raw", index);
    FILE *fp = fopen(fname, "wb");
    fwrite(t->buf, sizeof(UTFLOAT), t->size, fp);
    fclose(fp);
    return UT_OK;
}

int ut_test_verify(ut_test *t, const char *refhash)
{
    if(t->mode == NORMAL) {
        int fail = 0;
        if(ut_test_compare(t, refhash) == UT_NOT_OK) {
            printf("Generated hash %s does not match reference hash %s\n", 
                    t->md5string, refhash);
            fail = 1;
        }
        return fail;
    } else {
        ut_test_entry *tst = t->cur_entry;
        ut_test_compare(t, refhash);
        printf("TEST(t_%s, \"%s\", \"%s\")\n",
                tst->desc, tst->desc, t->md5string);
        return 0;
    }
}
