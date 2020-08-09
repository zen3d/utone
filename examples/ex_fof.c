#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_fof *fof;
    ut_ftbl *sine;
    ut_ftbl *win;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, fof = 0;
    ut_fof_compute(ut, ud->fof, &osc, &fof);
    ut->out[0] = fof;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_ftbl_create(ut, &ud.sine, 2048);
    ut_ftbl_create(ut, &ud.win, 1024);
    ut_fof_create(&ud.fof);

    ut_gen_sine(ut, ud.sine);
    ut_gen_composite(ut, ud.win, "0.5 0.5 270 0.5");

    ut_fof_init(ut, ud.fof, ud.sine, ud.win, 100, 0);

    ut->len = 44100 * 10;
    ut_process(ut, &ud, process);

    ut_fof_destroy(&ud.fof);
    ut_ftbl_destroy(&ud.sine);
    ut_ftbl_destroy(&ud.win);

    ut_destroy(&ut);
    return 0;
}
