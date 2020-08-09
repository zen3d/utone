#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_gbuzz *buzz;
    ut_ftbl *ft; 
    int counter;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    ut_gbuzz_compute(ut, ud->buzz, NULL, &ut->out[0]);
}

int main() {
    srand(time(NULL));
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_gbuzz_create(&ud.buzz);

    ut_gen_sine(ut, ud.ft);
    ut_gbuzz_init(ut, ud.buzz, ud.ft, 0);
    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_ftbl_destroy(&ud.ft);
    ut_gbuzz_destroy(&ud.buzz);
    ut_destroy(&ut);
    return 0;
}
