#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_blsquare *blsquare;
    int counter;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    if(ud->counter == 0){
        *ud->blsquare->freq = 500 + rand() % 2000;
    }
    ut_blsquare_compute(ut, ud->blsquare, NULL, &ut->out[0]);
    ud->counter = (ud->counter + 1) % 4410;
}

int main() {
    srand(time(NULL));
    UserData ud;
    ud.counter = 0;
    ut_data *ut;
    ut_create(&ut);

    ut_blsquare_create(&ud.blsquare);

    ut_blsquare_init(ut, ud.blsquare);
    *ud.blsquare->freq = 500.0;
    *ud.blsquare->amp = 0.9;
    *ud.blsquare->width = 0.5;
    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_blsquare_destroy(&ud.blsquare);
    ut_destroy(&ut);
    return 0;
}
