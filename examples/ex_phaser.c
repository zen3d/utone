#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_phaser *phaser;
    ut_diskin *disk;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT disk1 = 0, disk2 = 0, phaser = 0, foo = 0;
    ut_diskin_compute(ut, ud->disk, NULL, &disk1);
    disk2 = disk1;
    ut_phaser_compute(ut, ud->phaser, &disk1, &disk2, &phaser, &foo);
    ut->out[0] = phaser;
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_phaser_create(&ud.phaser);
    ut_diskin_create(&ud.disk);

    ut_diskin_init(ut, ud.disk, "oneart.wav");
    ut_phaser_init(ut, ud.phaser);
    
    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_phaser_destroy(&ud.phaser);
    ut_diskin_destroy(&ud.disk);

    ut_destroy(&ut);
    return 0;
}
