#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_noise *ns;
} UserData;

void write_noise(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT in = 0;
    ut_noise_compute(ut, ud->ns, NULL, &ut->out[0]);
}
int main() {
    srand(time(NULL));
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_noise_create(&ud.ns);
    ut_noise_init(ut, ud.ns);
    ud.ns->amp = 0.5;
    ut->len = 44100 * 5;
    ut_process(ut, &ud, write_noise);
    ut_noise_destroy(&ud.ns);
    ut_destroy(&ut);
    return 0;
}
