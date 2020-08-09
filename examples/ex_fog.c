#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_fog *fog;
    ut_ftbl *wav;
    ut_ftbl *win;
    ut_phasor *phs;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT phs = 0, fog = 0;
    ut_phasor_compute(ut, ud->phs, NULL, &phs);
    ud->fog->spd = phs;
    ut_fog_compute(ut, ud->fog, NULL, &fog);
    ut->out[0] = fog;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_ftbl_loadfile(ut, &ud.wav, "oneart.wav");
    ut_ftbl_create(ut, &ud.win, 1024);
    ut_fog_create(&ud.fog);
    ut_phasor_create(&ud.phs);

    ut_gen_composite(ut, ud.win, "0.5 0.5 270 0.5");

    ut_fog_init(ut, ud.fog, ud.wav, ud.win, 100, 0);
    ud.fog->trans = 0.9;

    ut_phasor_init(ut, ud.phs, 0);
    ud.phs->freq = 0.3 / ((UTFLOAT)ud.wav->size / ut->sr); 

    ut->len = 44100 * 10;
    ut_process(ut, &ud, process);

    ut_fog_destroy(&ud.fog);
    ut_ftbl_destroy(&ud.wav);
    ut_ftbl_destroy(&ud.win);
    ut_phasor_destroy(&ud.phs);

    ut_destroy(&ut);
    return 0;
}
