#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_osc *osc;
    ut_ftbl *ft; 
    int counter;
} UserData;

void write_osc(ut_data *ut, void *udata) {
    UserData *ud = udata;
    //if(udp->counter == 0){
    //    udp->osc->freq = 500 + rand() % 2000;
    //}
    ut_osc_compute(ut, ud->osc, NULL, &ut->out[0]);
    ud->counter = (ud->counter + 1) % 4410;
}

int main() {
    srand(time(NULL));
    UserData ud;
    ud.counter = 0;
    ut_data *ut;
    ut_create(&ut);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_osc_create(&ud.osc);
    
    ut_gen_file(ut, ud.ft, "Formant04.wav");
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ud.osc->freq = 440;
    ut->len = 44100 * 5;
    ut_process(ut, &ud, write_osc);

    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_destroy(&ut);
    return 0;
}
