#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

#define NOSC 5

typedef struct {
    ut_talkbox *talkbox;
    ut_blsaw *saw[NOSC];
    ut_diskin *diskin;
} UserData;

static int chord[] = {48, 51, 55, 60, 70};

static UTFLOAT process(ut_data *ut, void *udata) {
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
    return talkbox;
}

int t_talkbox(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    UserData ud;
    int fail = 0;
    int i;
    UTFLOAT tmp;

    /* allocate / initialize modules here */
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

    ut_diskin_init(ut, ud.diskin, SAMPDIR "oneart.wav");


    for(n = 0; n < tst->size; n++) {
    	tmp = process(ut, &ud);
        ut_test_add_sample(tst, tmp);
    }

    fail = ut_test_verify(tst, hash);

    ut_talkbox_destroy(&ud.talkbox);
    for(i = 0; i < NOSC; i ++) {
		ut_blsaw_destroy(&ud.saw[i]);
    }
    ut_diskin_destroy(&ud.diskin);

    if(fail) return UT_NOT_OK;
    else return UT_OK;
}
