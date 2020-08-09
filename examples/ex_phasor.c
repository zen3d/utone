#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_phasor *phs;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    ut_phasor_compute(ut, ud->phs, NULL, &ut->out[0]);
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_phasor_create(&ud.phs);

    ut_phasor_init(ut, ud.phs, 0);
    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_phasor_destroy(&ud.phs);
    ut_destroy(&ut);
    return 0;
}
