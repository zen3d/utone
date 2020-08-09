#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_paulstretch *paulstretch;
    ut_ftbl *ft; 
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT paulstretch = 0;
    ut_paulstretch_compute(ut, ud->paulstretch, NULL, &paulstretch);
    ut->out[0] = paulstretch;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_paulstretch_create(&ud.paulstretch);
    ut_ftbl_loadfile(ut, &ud.ft, "oneart.wav");

    ut_paulstretch_init(ut, ud.paulstretch, ud.ft, 1.0, 10);

    ut->len = 44100 * 20;
    ut_process(ut, &ud, process);

    ut_paulstretch_destroy(&ud.paulstretch);
    ut_ftbl_destroy(&ud.ft);

    ut_destroy(&ut);
    return 0;
}
