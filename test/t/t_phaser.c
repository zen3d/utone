#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_phaser *phaser;
    ut_diskin *disk;
} UserData;

int t_phaser(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;

    UTFLOAT disk1 = 0, disk2 = 0, phaser = 0, foo = 0;
    UserData ud;

    ut_phaser_create(&ud.phaser);
    ut_diskin_create(&ud.disk);

    ut_diskin_init(ut, ud.disk, SAMPDIR "oneart.wav");
    ut_phaser_init(ut, ud.phaser);
    
    for(n = 0; n < tst->size; n++) {
        disk1 = 0; disk2 = 0; phaser = 0; foo = 0;
        ut_diskin_compute(ut, ud.disk, NULL, &disk1);
        disk2 = disk1;
        ut_phaser_compute(ut, ud.phaser, &disk1, &disk2, &phaser, &foo);
        ut_test_add_sample(tst, phaser);
    }

    fail = ut_test_verify(tst, hash);

    ut_phaser_destroy(&ud.phaser);
    ut_diskin_destroy(&ud.disk);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
