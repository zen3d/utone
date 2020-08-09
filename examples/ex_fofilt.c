#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_noise *ns;
    ut_fofilt *tn;
} UserData;

void write_noise(ut_data *data, void *ud) {
    UserData *udata = ud;
    UTFLOAT in = 0;
    UTFLOAT out = 0;
    ut_noise_compute(data, udata->ns, NULL, &in);
    ut_fofilt_compute(data, udata->tn, &in, &data->out[0]); 
}
int main() {
    srand(time(NULL));
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_noise_create(&ud.ns);
    ut_fofilt_create(&ud.tn);
    ut_noise_init(ut, ud.ns);
    ut_fofilt_init(ut, ud.tn);
    ud.tn->freq = 500;
    ut->len = 44100 * 5;
    ut_process(ut, &ud, write_noise);
    ut_noise_destroy(&ud.ns);
    ut_fofilt_destroy(&ud.tn);
    ut_destroy(&ut);
    return 0;
}
