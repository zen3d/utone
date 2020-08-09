#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "utone.h"

typedef struct {
    ut_noise *ns;
    ut_eqfil *eqfil;
    int counter;
} UserData;

void write_noise(ut_data *data, void *ud) {
    UserData *udata = ud;
    UTFLOAT in = 0;
    UTFLOAT out = 0;
    if(udata->counter == 0) {
        udata->eqfil->freq = 500 + rand() % 4000;
        udata->eqfil->bw = fabs(udata->eqfil->freq * 0.5);
    }
    ut_noise_compute(data, udata->ns, NULL, &in);
    ut_eqfil_compute(data, udata->eqfil, &in, &data->out[0]); 
    udata->counter = (udata->counter + 1) % 5000;
}
int main() {
    srand(time(NULL));
    UserData ud;
    ud.counter = 0;
    ut_data *ut;
    ut_create(&ut);
    ut_noise_create(&ud.ns);
    ut_eqfil_create(&ud.eqfil);
    ut_noise_init(ut, ud.ns);
    ut_eqfil_init(ut, ud.eqfil);
    ut->len = 44100 * 5;
    ut_process(ut, &ud, write_noise);
    ut_noise_destroy(&ud.ns);
    ut_eqfil_destroy(&ud.eqfil);
    ut_destroy(&ut);
    return 0;
}
