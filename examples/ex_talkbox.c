#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

#define NOSC 5

typedef struct {
    ut_talkbox *talkbox;
    ut_blsaw *saw[NOSC];
    ut_diskin *diskin;
} UserData;

static int chord[] = {48, 51, 55, 60, 70};

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT tmp;
    int i;
    UTFLOAT src = 0;
    UTFLOAT exc = 0;
    UTFLOAT talkbox = 0;

    exc = 0;
    for(i = 0; i < NOSC; i++) {
		ut_blsaw_compute(ut, ud->saw[i], NULL, &tmp);
		exc += tmp;
    }
    ut_diskin_compute(ut, ud->diskin, NULL, &src);
    src *= 0.5;
    ut_talkbox_compute(ut, ud->talkbox, &src, &exc, &talkbox);
    ut_out(ut, 0, talkbox);
}

int main() {
    UserData ud;
    ut_data *ut;
    int i;
    ut_create(&ut);
    ut_srand(ut, 1234567);

    ut_diskin_create(&ud.diskin);
	ut_talkbox_create(&ud.talkbox);
	ut_talkbox_init(ut, ud.talkbox);
	ud.talkbox->quality = 0.2;

	for(i = 0; i < NOSC; i++) {
		ut_blsaw_create(&ud.saw[i]);
		ut_blsaw_init(ut, ud.saw[i]);
		*ud.saw[i]->freq = ut_midi2cps(chord[i]);
		*ud.saw[i]->amp = 0.1;
    }

    ut_diskin_init(ut, ud.diskin, "oneart.wav");

    ut->len = 44100 * 8;
    ut_process(ut, &ud, process);

    ut_talkbox_destroy(&ud.talkbox);
    for(i = 0; i < NOSC; i ++) {
		ut_blsaw_destroy(&ud.saw[i]);
    }
    ut_diskin_destroy(&ud.diskin);

    ut_destroy(&ut);
    return 0;
}
