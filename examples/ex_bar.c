#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_bar *bar;
    ut_metro *met;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT bar = 0, met = 0;
    ut_metro_compute(ut, ud->met, NULL, &met);
    ut_bar_compute(ut, ud->bar, &met, &bar);
    ut->out[0] = bar;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_bar_create(&ud.bar);
    ut_metro_create(&ud.met);

    ut_bar_init(ut, ud.bar, 3, 0.0001);
    ud.bar->T30 = 1;

    ut_metro_init(ut, ud.met);
    ud.met->freq = 1;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_bar_destroy(&ud.bar);
    ut_metro_destroy(&ud.met);

    ut_destroy(&ut);
    return 0;
}
