typedef struct {
    int mti;
    /* do not change value 624 */
    uint32_t mt[624];
} ut_randmt;

void ut_randmt_seed(ut_randmt *p,
    const uint32_t *initKey, uint32_t keyLength);

uint32_t ut_randmt_compute(ut_randmt *p);
