#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_noise *ns;
    ut_moogladder *moog;
    int counter;
} UserData;

void write_noise(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT in = 0;
    UTFLOAT out = 0;
    if(ud->counter == 0) {
        ud->moog->res = 0.8;
        ud->moog->freq = 500 + rand() % 4000;
    }
    ut_noise_compute(ut, ud->ns, NULL, &in);
    ut_moogladder_compute(ut, ud->moog, &in, &ut->out[0]); 
    ud->counter = (ud->counter + 1) % 5000;
}
int main() {
    srand(time(NULL));
    UserData ud;
    ud.counter = 0;
    ut_data *ut;
    ut_create(&ut);
    ut_noise_create(&ud.ns);
    ut_moogladder_create(&ud.moog);
    ut_noise_init(ut, ud.ns);
    ut_moogladder_init(ut, ud.moog);
    ut->len = 44100 * 5;
    ut_process(ut, &ud, write_noise);
    ut_noise_destroy(&ud.ns);
    ut_moogladder_destroy(&ud.moog);
    ut_destroy(&ut);
    return 0;
}
