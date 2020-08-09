#include "utone.h"


typedef struct user_data {
    ut_ftbl *ft, *amps;
    ut_osc *osc;
    UTFLOAT fc;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    //ut->out = ud->ft->tbl[ut->pos % ud->ft->size];
    ut_osc_compute(ut, ud->osc, NULL, &ut->out[0]);
}

int main() {
    UserData ud;
    int i;
    ut_data *ut;
    ut_create(&ut); ut_ftbl_create(ut, &ud.amps, 64);
    ut_ftbl_create(ut, &ud.ft, 262144);
    ut_osc_create(&ud.osc);

    ut->sr = 96000;
    //ut->len = ud.ft->size;
    ut->len = ut->sr * 5;
    ud.amps->tbl[0] = 0.0;

    for(i = 1; i < ud.amps->size; i++){
        ud.amps->tbl[i] = 1.0 / i;
        if((i % 2) == 0) ud.amps->tbl[i] *= 2.0; 
    }

    
    /* Discovered empirically. multiply frequency by this constant. */
    ud.fc = 1 / (6.0 * 440); 
    ut_gen_padsynth(ut, ud.ft, ud.amps, ut_midi2cps(60), 40.0);

    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->freq = ut_midi2cps(70) * ud.fc;
    ud.osc->amp = 1.0;
    ut_process(ut, &ud, process);

    ut_osc_destroy(&ud.osc);
    ut_ftbl_destroy(&ud.amps);
    ut_ftbl_destroy(&ud.ft);
    return 0;
}
