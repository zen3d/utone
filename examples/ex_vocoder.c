#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_vocoder *vocoder;
    ut_blsaw *saw[3];
    ut_diskin *diskin;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    int i;
    UTFLOAT diskin = 0, vocoder = 0, saw = 0, tmp = 0;
    ut_diskin_compute(ut, ud->diskin, NULL, &diskin);
    for(i = 0; i < 3; i++) {
        ut_blsaw_compute(ut, ud->saw[i], NULL, &tmp);
        saw += tmp;
    }
    saw *= 0.2;
    ut_vocoder_compute(ut, ud->vocoder, &diskin, &saw, &vocoder);
    ut->out[0] = vocoder;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    int i;

    int scale[] = {58, 65, 72};

    ut_vocoder_create(&ud.vocoder);
    ut_vocoder_init(ut, ud.vocoder);
   
    ut_diskin_create(&ud.diskin); 
    ut_diskin_init(ut, ud.diskin, "oneart.wav");

    for(i = 0; i < 3; i++) {
        ut_blsaw_create(&ud.saw[i]);
        ut_blsaw_init(ut, ud.saw[i]);
        *ud.saw[i]->freq = ut_midi2cps(scale[i]);
    }

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_vocoder_destroy(&ud.vocoder);
    for(i = 0; i < 3; i++) {
        ut_blsaw_destroy(&ud.saw[i]);
    }
    ut_diskin_destroy(&ud.diskin); 

    ut_destroy(&ut);
    return 0;
}
