#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_noise *ns;
    ut_streson *stres;
} UserData;

void write_noise(ut_data *data, void *ud) {
    UserData *udata = ud;
    UTFLOAT in = 0;
    UTFLOAT noise = 0;
    ut_noise_compute(data, udata->ns, NULL, &noise);
    ut_streson_compute(data, udata->stres, &noise, &data->out[0]);
}
int main() {
    srand(time(NULL));
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_streson_create(&ud.stres);
    ut_noise_create(&ud.ns);
    ut_noise_init(ut, ud.ns);
    ut_streson_init(ut, ud.stres);
    ut->len = 44100 * 5;
    ut_process(ut, &ud, write_noise);
    ut_noise_destroy(&ud.ns);
    ut_streson_destroy(&ud.stres);
    ut_destroy(&ut);
    return 0;
}
