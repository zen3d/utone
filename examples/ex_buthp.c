#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_noise *ns;
    ut_buthp *buthp;
} UserData;

void write_noise(ut_data *data, void *ud) {
    UserData *udata = ud;
    UTFLOAT in = 0;
    UTFLOAT out = 0;
    ut_noise_compute(data, udata->ns, NULL, &in);
    ut_buthp_compute(data, udata->buthp, &in, &data->out[0]); 
}
int main() {
    srand(time(NULL));
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_noise_create(&ud.ns);
    ut_buthp_create(&ud.buthp);
    ut_noise_init(ut, ud.ns);
    ut_buthp_init(ut, ud.buthp);
    ud.buthp->freq = 5000;
    ut->len = 44100 * 5;
    ut_process(ut, &ud, write_noise);
    ut_noise_destroy(&ud.ns);
    ut_buthp_destroy(&ud.buthp);
    ut_destroy(&ut);
    return 0;
}
