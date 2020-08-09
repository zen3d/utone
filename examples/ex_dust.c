#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_dust *dst;
} UserData;

void write_dust(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT in = 0;
    ut_dust_compute(ut, ud->dst, NULL, &ut->out[0]);
}
int main() {
    srand(time(NULL));
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_dust_create(&ud.dst);
    ut_dust_init(ut, ud.dst);
    ud.dst->amp = 0.3;
    ud.dst->density = 30;
    ut->len = 44100 * 5;
    ud.dst->bipolar = 1.0;
    ut_process(ut, &ud, write_dust);
    ut_dust_destroy(&ud.dst);
    ut_destroy(&ut);
    return 0;
}
