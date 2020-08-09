#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_pluck *pluck;
    ut_metro *met;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT pluck = 0, met = 0;
    ut_metro_compute(ut, ud->met, NULL, &met);
    UTFLOAT notes[] = {60, 63, 67, 70, 74};
    if(met) {
        ud->pluck->freq = ut_midi2cps(notes[ut_rand(ut) % 5]);
    }
    ut_pluck_compute(ut, ud->pluck, &met, &pluck);
    ut->out[0] = pluck;
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 1234567);

    ut_pluck_create(&ud.pluck);
    ut_metro_create(&ud.met);

    ut_pluck_init(ut, ud.pluck, 400);
    ut_metro_init(ut, ud.met);
    ud.met->freq = 4;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_pluck_destroy(&ud.pluck);
    ut_metro_destroy(&ud.met);

    ut_destroy(&ut);
    return 0;
}
