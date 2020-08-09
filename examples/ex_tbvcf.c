#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_noise *ns;
    ut_tbvcf *tn;
} UserData;

void write_noise(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT in = 0;
    UTFLOAT out = 0;
    ut_noise_compute(ut, ud->ns, NULL, &in);
    ut_tbvcf_compute(ut, ud->tn, &in, &ut->out[0]); 
}
int main() {
    srand(time(NULL));
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_noise_create(&ud.ns);
    ut_tbvcf_create(&ud.tn);
    ut_noise_init(ut, ud.ns);
    ut_tbvcf_init(ut, ud.tn);
    ut->len = 44100 * 5;
    ud.tn->dist = 1.0;
    ut_process(ut, &ud, write_noise);
    ut_noise_destroy(&ud.ns);
    ut_tbvcf_destroy(&ud.tn);
    ut_destroy(&ut);
    return 0;
}
