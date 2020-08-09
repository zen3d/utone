#include <stdio.h>
#include "utone.h"

typedef struct {
   ut_ftbl *ft;
   ut_osc *osc;
   ut_clip *clp;
   ut_moogladder *filt;
} UserData;

void write_clip(ut_data *ut, void *ud) {
    UserData *udp = ud;
    UTFLOAT out, osc, filt;
    ut_osc_compute(ut, udp->osc, NULL, &osc);
    ut_moogladder_compute(ut, udp->filt, &osc, &filt);
    ut_clip_compute(ut, udp->clp, &filt, &out);
    ut->out[0] = out;
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_clip_create(&ud.clp);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 4096);
    ut_moogladder_create(&ud.filt);

    ut_gen_line(ut, ud.ft, "0 1 4096 -1");
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->freq = ut_midi2cps(48);
    ut_clip_init(ut, ud.clp);
    ut_moogladder_init(ut, ud.filt);
    ud.filt->freq = 1000; 
    ud.filt->res = 0.8;
    ut->len = 44100 * 5;
    ut_process(ut, &ud, write_clip);

    ut_osc_destroy(&ud.osc);
    ut_clip_destroy(&ud.clp);
    ut_ftbl_destroy(&ud.ft);
    ut_moogladder_destroy(&ud.filt);

    ut_destroy(&ut);
    return 0;
}
