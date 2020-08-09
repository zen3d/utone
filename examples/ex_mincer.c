#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_mincer *mincer;
    ut_ftbl *ft; 
    ut_randi *randi;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, mincer = 0, randi = 0;
    
    ut_randi_compute(ut, ud->randi, NULL, &randi);
    ud->mincer->time = randi;
    ud->mincer->amp = 1;
    ud->mincer->pitch = 1;
    ut_mincer_compute(ut, ud->mincer, NULL, &mincer);
    ut->out[0] = mincer;
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 1234567);

    ut_mincer_create(&ud.mincer);
    /* allocates loads an audio file into a ftable */
    ut_ftbl_loadfile(ut, &ud.ft, "oneart.wav");

    ut_randi_create(&ud.randi);

    ut_mincer_init(ut, ud.mincer, ud.ft, 16384);
    ut_randi_init(ut, ud.randi);
    ud.randi->min = 0;
    ud.randi->max = 1;
    ud.randi->cps = 1;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_mincer_destroy(&ud.mincer);
    ut_ftbl_destroy(&ud.ft);
    ut_randi_destroy(&ud.randi);

    ut_destroy(&ut);
    return 0;
}
