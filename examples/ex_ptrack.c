#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_ptrack *ptrack;
    ut_osc *osc;
    ut_ftbl *ft;
    ut_blsaw *sig;
    ut_randh *randh;
    ut_port *port;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT freq = 0, amp = 0, sig = 0, randh = 0, osc = 0;
    UTFLOAT portfreq = 0;
    ut_randh_compute(ut, ud->randh, NULL, &randh);
    ut_port_compute(ut, ud->port, &randh, &portfreq);
    *ud->sig->freq = portfreq;
    ut_blsaw_compute(ut, ud->sig, NULL, &sig);
    ut_ptrack_compute(ut, ud->ptrack, &sig, &freq, &amp);
    ud->osc->freq = freq * 2;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut->out[0] = (osc + sig * 0.1) * 0.5;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_ptrack_create(&ud.ptrack);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 4096);
    ut_blsaw_create(&ud.sig);
    ut_randh_create(&ud.randh);
    ut_port_create(&ud.port);

    ut_ptrack_init(ut, ud.ptrack, 512, 20);
    ut_randh_init(ut, ud.randh);
    ud.randh->max = 500;
    ud.randh->min = 200;
    ud.randh->freq = 6;
    ut_port_init(ut, ud.port, 0.005);

    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);

    ut_blsaw_init(ut, ud.sig);
    *ud.sig->amp = 0.5;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_blsaw_destroy(&ud.sig);
    ut_randh_destroy(&ud.randh);
    ut_ptrack_destroy(&ud.ptrack);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_port_destroy(&ud.port);

    ut_destroy(&ut);
    return 0;
}
