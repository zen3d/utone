#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_drip *drip;
    ut_dust *trig;
    ut_revsc *rev;
} UserData;

void write_osc(ut_data *ut, void *ud) {
    UserData *udp = ud;
    UTFLOAT trig, rev1, rev2, drip;
    ut_dust_compute(ut, udp->trig, NULL, &trig);
    ut_drip_compute(ut, udp->drip, &trig, &drip);
    ut_revsc_compute(ut, udp->rev, &drip, &drip, &rev1, &rev2);
    ut->out[0] = drip + rev1 * 0.05;
}

int main() {
    srand(time(NULL));
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_revsc_create(&ud.rev);
    ut_drip_create(&ud.drip);
    ut_dust_create(&ud.trig);
    
    ut_dust_init(ut, ud.trig);
    ud.trig->amp = 1;
    ud.trig->density = 1;
    ut_drip_init(ut, ud.drip, 0.09);
    ud.drip->amp = 0.3;
    ut_revsc_init(ut, ud.rev);
    ud.rev->feedback = 0.9;
    
    ut->len = 44100 * 30;
    ut_process(ut, &ud, write_osc);
    ut_drip_destroy(&ud.drip);
    ut_dust_destroy(&ud.trig);
    ut_revsc_destroy(&ud.rev);
    ut_destroy(&ut);
    return 0;
}
