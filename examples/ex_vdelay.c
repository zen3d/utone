#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_osc *osc, *lfo;
    ut_ftbl *ft, *sine;
    ut_vdelay *del;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT freq = 0.0, del = 0.0, osc = 0.0;
    ut_osc_compute(ut, ud->lfo, NULL, &freq);
    freq = 1.0 + (freq * 0.5);
    freq = 0.02 + (freq * 0.02);
    ud->del->del = freq;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut_vdelay_compute(ut, ud->del, &osc, &del);
    ut->out[0] = del * 0.5 + osc * 0.5;
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_vdelay_create(&ud.del);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.sine, 4096);
    ut_osc_create(&ud.lfo);

    ut_vdelay_init(ut, ud.del, 0.5);
    ut_gen_file(ut, ud.ft, "Formant04.wav");
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->freq = ut_midi2cps(50);

    ut_gen_sine(ut, ud.sine);
    ut_osc_init(ut, ud.lfo, ud.sine, 0);
    ud.lfo->freq = 0.2;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_vdelay_destroy(&ud.del);
    ut_ftbl_destroy(&ud.ft);
    ut_ftbl_destroy(&ud.sine);
    ut_osc_destroy(&ud.osc);
    ut_osc_destroy(&ud.lfo);
    ut_destroy(&ut);
    return 0;
}
