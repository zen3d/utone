#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_saturator *saturator;
    ut_diskin *diskin;
    ut_dcblock *dcblk;
} UserData;

void process(ut_data *ut, void *udata) 
{
    UserData *ud = udata;
    UTFLOAT diskin = 0, saturator = 0, dcblk = 0;
    ut_diskin_compute(ut, ud->diskin, NULL, &diskin);
    ut_saturator_compute(ut, ud->saturator, &diskin, &saturator);
    ut_dcblock_compute(ut, ud->dcblk, &saturator, &dcblk);
    ut_out(ut, 0, dcblk);
}

int main() 
{
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 1234567);

    ut_saturator_create(&ud.saturator);
    ut_diskin_create(&ud.diskin);
    ut_dcblock_create(&ud.dcblk);

    ut_saturator_init(ut, ud.saturator);
    ut_diskin_init(ut, ud.diskin, "oneart.wav");
    ut_dcblock_init(ut, ud.dcblk);

    ud.saturator->drive = 10;
    ud.saturator->dcoffset = 4;
    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_saturator_destroy(&ud.saturator);
    ut_diskin_destroy(&ud.diskin);
    ut_dcblock_destroy(&ud.dcblk);

    ut_destroy(&ut);
    return 0;
}
