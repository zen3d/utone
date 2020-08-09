#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_diode *diode;
    ut_noise *ns;
    ut_osc *lfo;
    ut_ftbl *ft;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT ns = 0;
    UTFLOAT diode = 0;
    UTFLOAT lfo = 0;
    ut_osc_compute(ut, ud->lfo, NULL, &lfo);
    ut_noise_compute(ut, ud->ns, NULL, &ns);
    ud->diode->freq = 2000 + lfo * 1800;
    ut_diode_compute(ut, ud->diode, &ns, &diode);
    ut_out(ut, 0, diode);
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 1234567);

    ut_diode_create(&ud.diode);
    ut_noise_create(&ud.ns);
    ut_osc_create(&ud.lfo);
    ut_ftbl_create(ut, &ud.ft, 8192);
    ut_gen_sine(ut, ud.ft);

    ut_diode_init(ut, ud.diode);
    ut_noise_init(ut, ud.ns);
    ut_osc_init(ut, ud.lfo, ud.ft, 0);
    ud.lfo->freq = 0.5;
    ud.lfo->amp = 1.0;
    ud.diode->res = 0.9;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_diode_destroy(&ud.diode);
    ut_noise_destroy(&ud.ns);
    ut_osc_destroy(&ud.lfo);

    ut_destroy(&ut);
    return 0;
}
