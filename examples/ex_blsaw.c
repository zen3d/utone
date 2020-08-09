#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_blsaw *blsaw;
    int counter;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    if(ud->counter == 0){
        *ud->blsaw->freq = 500 + rand() % 2000;
    }
    ut_blsaw_compute(ut, ud->blsaw, NULL, &ut->out[0]);
    ud->counter = (ud->counter + 1) % 4410;
}

int main() {
    srand(time(NULL));
    UserData ud;
    ud.counter = 0;
    ut_data *ut;
    ut_create(&ut);

    ut_blsaw_create(&ud.blsaw);

    ut_blsaw_init(ut, ud.blsaw);
    *ud.blsaw->freq = 500;
    *ud.blsaw->amp = 1;
    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_blsaw_destroy(&ud.blsaw);
    ut_destroy(&ut);
    return 0;
}
