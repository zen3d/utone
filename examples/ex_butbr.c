#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_butbr *butbr;
    ut_noise *ns;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT noise = 0, butbr = 0;
    ut_noise_compute(ut, ud->ns, NULL, &noise);
    ut_butbr_compute(ut, ud->butbr, &noise, &butbr);
    ut->out[0] = butbr;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_butbr_create(&ud.butbr);
    ut_noise_create(&ud.ns);

    ut_butbr_init(ut, ud.butbr);
    ut_noise_init(ut, ud.ns);

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_butbr_destroy(&ud.butbr);
    ut_noise_destroy(&ud.ns);

    ut_destroy(&ut);
    return 0;
}
