#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "utone.h"

#define NVOICES 5


typedef struct oscil{
    ut_osc *osc;
    ut_randi *rnd;
}oscil;

typedef struct {
    //ut_osc *osc;
    //ut_randi *rnd;
    oscil v[NVOICES];
    ut_ftbl *ft;
    ut_revsc *rev;
    ut_dcblock *dcblk;
} UserData;

UTFLOAT midi2cps(int nn){
    return pow(2, (nn - 69.0) / 12.0) * 440.0;
}

void write_osc(ut_data *data, void *ud) {
    UserData *udp = ud;
    int i;
    UTFLOAT amp = 0;
    UTFLOAT osc = 0;
    UTFLOAT dry = 0;
    UTFLOAT wet = 0;
    UTFLOAT blk = 0;
    UTFLOAT foo = 0;
    for(i = 0; i < NVOICES; i++){
        ut_randi_compute(data, udp->v[i].rnd, NULL, &amp);
        ut_osc_compute(data, udp->v[i].osc, NULL, &osc);
        dry += osc * amp;
    }
    ut_revsc_compute(data, udp->rev, &dry, &dry, &wet, &foo);

    ut_dcblock_compute(data, udp->dcblk, &wet, &blk);
    data->out[0] = 0.5 * dry + 0.3 * wet;
}

int main() {
    srand(time(NULL));
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    int notes[] = { 60, 67, 71, 74, 76 };
    int i;

    ut_dcblock_create(&ud.dcblk);
    ut_revsc_create(&ud.rev);
    ut_ftbl_create(ut, &ud.ft, 2048);

    ut_gen_file(ut, ud.ft, "FMSine111.wav");
    for(i = 0; i < NVOICES; i++){
        ut_osc_create(&ud.v[i].osc);
        ut_randi_create(&ud.v[i].rnd);
        ut_osc_init(ut, ud.v[i].osc, ud.ft, 0);
        ud.v[i].osc->amp = 0.3;
        ud.v[i].osc->freq = midi2cps(notes[i]);
        ut_randi_init(ut, ud.v[i].rnd);
        ud.v[i].rnd->cps = 0.8;
    }

    ut_revsc_init(ut, ud.rev);
    ut_dcblock_init(ut, ud.dcblk);
    ut->len = 44100 * 40;

    ut_process(ut, &ud, write_osc);

    ut_revsc_destroy(&ud.rev);
    ut_dcblock_destroy(&ud.dcblk);
    ut_ftbl_destroy(&ud.ft);
    for(i = 0; i < NVOICES; i++){
        ut_osc_destroy(&ud.v[i].osc);
        ut_randi_destroy(&ud.v[i].rnd);
    }
    ut_destroy(&ut);
    return 0;
}
