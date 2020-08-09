#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_noise *ns;
    ut_butbp *butbp;
    int counter;
} UserData;

void write_noise(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT in = 0;
    UTFLOAT out = 0;
    if(ud->counter == 0) {
        ud->butbp->freq= 500 + rand() % 4000;
    }
    ut_noise_compute(ut, ud->ns, NULL, &in);
    ut_butbp_compute(ut, ud->butbp, &in, &ut->out[0]); 
    ud->counter = (ud->counter + 1) % 5000;
}
int main() {
    srand(time(NULL));
    UserData ud;
    ud.counter = 0;
    ut_data *ut;
    ut_create(&ut);
    ut_noise_create(&ud.ns);
    ut_butbp_create(&ud.butbp);
    ut_noise_init(ut, ud.ns);
    ut_butbp_init(ut, ud.butbp);
    ut->len = 44100 * 5;
    ut_process(ut, &ud, write_noise);
    ut_noise_destroy(&ud.ns);
    ut_butbp_destroy(&ud.butbp);
    ut_destroy(&ut);
    return 0;
}
