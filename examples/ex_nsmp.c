#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_metro *met;
    ut_nsmp *nsmp;
    ut_ftbl *ft;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT met = 0, nsmp = 0;
    ut_metro_compute(ut, ud->met, NULL, &met);
    if(met) {
        ud->nsmp->index = rand() % 3;
    }
    ut_nsmp_compute(ut, ud->nsmp, &met, &nsmp);
    ut->out[0] = nsmp;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_ftbl_loadfile(ut, &ud.ft, "oneart.wav");
    ut_nsmp_create(&ud.nsmp);
    ut_metro_create(&ud.met);

    ut_metro_init(ut, ud.met);
    ud.met->freq = 2;
    ut_nsmp_init(ut, ud.nsmp, ud.ft, 44100, "oneart.ini");

    ut_nsmp_print_index(ut, ud.nsmp);

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_nsmp_destroy(&ud.nsmp);
    ut_metro_destroy(&ud.met);

    ut_ftbl_destroy(&ud.ft);

    ut_destroy(&ut);
    return 0;
}
