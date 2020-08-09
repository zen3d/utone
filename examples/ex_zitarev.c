#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_diskin *disk;
    ut_zitarev *rev;
    int counter;
} UserData;

void process(ut_data *ut , void *udata) {
    UserData *ud = udata;
    UTFLOAT in = 0;
    UTFLOAT out = 0;
    UTFLOAT foo = 0;

    ut_diskin_compute(ut, ud->disk, NULL, &in);
    ut_zitarev_compute(ut, ud->rev, &in, &in, &ut->out[0], &foo);
}

int main() {
    srand(time(NULL));
    UserData ud;
    ud.counter = 0;
    ut_data *ut;
    ut_create(&ut);
    ut_diskin_create(&ud.disk);
    ut_zitarev_create(&ud.rev);

    ut_diskin_init(ut, ud.disk, "oneart.wav");
    ut_zitarev_init(ut, ud.rev);
    *ud.rev->level = 0;
    *ud.rev->in_delay = 20;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_diskin_destroy(&ud.disk);
    ut_zitarev_destroy(&ud.rev);
    ut_destroy(&ut);
    return 0;
}
