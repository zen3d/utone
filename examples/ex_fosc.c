#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_fosc *osc;
    ut_ftbl *ft; 
    int counter;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = ud;
    if(ud->counter == 0){
        ud->osc->freq = 500 + rand() % 2000;
    }
    ut_fosc_compute(ut, ud->osc, NULL, &ut->out[0]);
    ud->counter = (ud->counter + 1) % 4410;
}

int main() {
    srand(time(NULL));
    UserData ud;
    ud.counter = 0;
    ut_data *ut;
    ut_create(&ut);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_fosc_create(&ud.osc);

    ut_gen_sine(ut, ud.ft);
    ut_fosc_init(ut, ud.osc, ud.ft);
    ud.osc->freq = 500;
    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_ftbl_destroy(&ud.ft);
    ut_fosc_destroy(&ud.osc);
    ut_destroy(&ut);
    return 0;
}
