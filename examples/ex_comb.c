#include "utone.h"

typedef struct {
    ut_comb *comb;
    ut_diskin *disk;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT comb = 0, disk = 0;
    ut_diskin_compute(ut, ud->disk, NULL, &disk);
    disk *= 0.5;
    ut_comb_compute(ut, ud->comb, &disk, &comb);

    ut->out[0] = comb;
}


int main()
{
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_comb_create(&ud.comb);

    ut_diskin_create(&ud.disk);

    ut_comb_init(ut, ud.comb, 0.01);
    ut_diskin_init(ut, ud.disk, "oneart.wav");
    
    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_comb_destroy(&ud.comb);
    ut_diskin_destroy(&ud.disk);
    ut_destroy(&ut);
    return 0;
}
