#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_bltriangle *bltriangle;
    int counter;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    if(ud->counter == 0){
        *ud->bltriangle->freq = 500 + rand() % 2000;
    }
    ut_bltriangle_compute(ut, ud->bltriangle, NULL, &ut->out[0]);
    ud->counter = (ud->counter + 1) % 4410;
}

int main() {
    srand(time(NULL));
    UserData ud;
    ud.counter = 0;
    ut_data *ut;
    ut_create(&ut);

    ut_bltriangle_create(&ud.bltriangle);

    ut_bltriangle_init(ut, ud.bltriangle);
    *ud.bltriangle->freq = 500.0;
    *ud.bltriangle->amp = 0.9;
    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_bltriangle_destroy(&ud.bltriangle);
    ut_destroy(&ut);
    return 0;
}
