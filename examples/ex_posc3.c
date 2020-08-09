#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_posc3 *posc3;
    ut_ftbl *ft; 
    int counter;
} UserData;

void write_posc3(ut_data *ut, void *udata) {
    UserData *ud = udata;
    if(ud->counter == 0){
        ud->posc3->freq = 500 + rand() % 2000;
    }
    ut_posc3_compute(ut, ud->posc3, NULL, &ut->out[0]);
    ud->counter = (ud->counter + 1) % 4410;
}

int main() {
    srand(time(NULL));
    UserData ud;
    ud.counter = 0;
    ut_data *ut;
    ut_create(&ut);
    ut_ftbl_create(ut, &ud.ft, 1024);
    ut_posc3_create(&ud.posc3);

    ut_gen_sine(ut, ud.ft);
    ut_posc3_init(ut, ud.posc3, ud.ft);
    ud.posc3->freq = 500;
    ut->len = 44100 * 5;
    ut_process(ut, &ud, write_posc3);

    ut_ftbl_destroy(&ud.ft);
    ut_posc3_destroy(&ud.posc3);
    ut_destroy(&ut);
    return 0;
}
