#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_noise *ns;
    ut_reson *reson;
} udata;

void write_noise(ut_data *data, void *ud) {
    udata *udata = ud;
    UTFLOAT in = 0;
    UTFLOAT out = 0;
    ut_noise_compute(data, udata->ns, NULL, &in);
    udata->reson->freq = 4000;
    udata->reson->bw = 1000;
    ut_reson_compute(data, udata->reson, &in, &out); 
    data->out[0] = out * 0.1;
}
int main() {
    udata ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 12345);
    ut_noise_create(&ud.ns);
    ut_reson_create(&ud.reson);
    ut_noise_init(ut, ud.ns);
    ud.ns->amp = 1.0;
    ut_reson_init(ut, ud.reson);
    ut->len = 44100 * 5;
    ut_process(ut, &ud, write_noise);
    ut_noise_destroy(&ud.ns);
    ut_reson_destroy(&ud.reson);
    ut_destroy(&ut);
    return 0;
}
