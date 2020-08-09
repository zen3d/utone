#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_osc *osc;
    ut_metro *mt;
    ut_ftbl *sine, *nn;
    ut_tseq *seq;
    ut_port *prt;
} UserData;

void process(ut_data *ut, void *userdata) {
    UserData *ud = userdata;
    UTFLOAT osc, mt, nn, freq, pfreq;
    ut_metro_compute(ut, ud->mt, NULL, &mt);
    ut_tseq_compute(ut, ud->seq, &mt, &nn);
    freq = ut_midi2cps(nn);
    ut_port_compute(ut, ud->prt, &freq, &pfreq);
    ud->osc->freq = pfreq;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut->out[0] = osc;
}

int main() {
    srand(time(NULL));
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_metro_create(&ud.mt);
    ut_ftbl_create(ut, &ud.sine, 2048);
    ut_ftbl_create(ut, &ud.nn, 1);
    ut_osc_create(&ud.osc);
    ut_port_create(&ud.prt);

    ut_gen_vals(ut, ud.nn, "60 63 65 60 63 67");
    ut_tseq_create(&ud.seq);
    ut_tseq_init(ut, ud.seq, ud.nn);

    ut_port_init(ut, ud.prt, 0.02);
    ut_metro_init(ut, ud.mt);
    ud.mt->freq = 4.0;
    ut_gen_sine(ut, ud.sine);
    ut_osc_init(ut, ud.osc, ud.sine, 0);
    ut->len = 44100 * 5;

    ut_process(ut, &ud, process);

    ut_port_destroy(&ud.prt);
    ut_tseq_destroy(&ud.seq);
    ut_metro_destroy(&ud.mt);
    ut_ftbl_destroy(&ud.sine);
    ut_ftbl_destroy(&ud.nn);
    ut_osc_destroy(&ud.osc);

    ut_destroy(&ut);
    return 0;
}
