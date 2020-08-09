#ifndef SAMPDIR
#define SAMPDIR "../examples/"
#endif

enum {
NORMAL,
HEADER
};
typedef struct {
    UTFLOAT *buf;
    uint32_t size;
    uint32_t pos;
    md5_state_t state;
    md5_byte_t digest[16];
    char md5string[33];
    char *md5;
    int mode;
    struct ut_test_entry *cur_entry;
} ut_test;

typedef struct ut_test_entry {
    int (* func)(ut_test *, ut_data *, const char*);
    const char *desc;
    const char *hash;
} ut_test_entry;

int ut_test_create(ut_test **t, uint32_t bufsize);
int ut_test_destroy(ut_test **t);
int ut_test_add_sample(ut_test *t, UTFLOAT sample);
/* Compares buffer with reference hash */
int ut_test_compare(ut_test *t, const char *md5hash);
/* verify wraps compare and error message up together */
int ut_test_verify(ut_test *t, const char *refhash);
int ut_test_write_raw(ut_test *t, uint32_t index);
