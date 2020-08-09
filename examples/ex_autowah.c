#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_autowah *autowah;
    ut_diskin *disk;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT disk = 0, autowah = 0;
    ut_diskin_compute(ut, ud->disk, NULL, &disk);
    ut_autowah_compute(ut, ud->autowah, &disk, &autowah);
    ut->out[0] = autowah;
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_autowah_create(&ud.autowah);
    ut_diskin_create(&ud.disk);

    ut_diskin_init(ut, ud.disk, "riff.wav");
    ut_autowah_init(ut, ud.autowah);
    *ud.autowah->wah = 1.0;
    
    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_autowah_destroy(&ud.autowah);
    ut_diskin_destroy(&ud.disk);

    ut_destroy(&ut);
    return 0;
}
