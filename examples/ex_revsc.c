#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_noise *ns;
    ut_revsc *rev;
    int counter;
} UserData;

void process(ut_data *data, void *ud) {
    UserData *udata = ud;
    UTFLOAT in = 0;
    UTFLOAT out = 0;
    UTFLOAT foo = 0;
    ut_noise_compute(data, udata->ns, NULL, &in);
    
    if(udata->counter < 2000) {
        udata->counter = (udata->counter + 1) % 5000;
    }else{
        in = 0;
    }
    ut_revsc_compute(data, udata->rev, &in, &in, &data->out[0], &foo); 
}

int main() {
    srand(time(NULL));
    UserData ud;
    ud.counter = 0;
    ut_data *ut;
    ut_create(&ut);
    ut_noise_create(&ud.ns);
    ut_revsc_create(&ud.rev);
    ut_noise_init(ut, ud.ns);
    ut_revsc_init(ut, ud.rev);

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_noise_destroy(&ud.ns);
    ut_revsc_destroy(&ud.rev);
    ut_destroy(&ut);
    return 0;
}
