#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_random *random;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT random = 0;
    ut_random_compute(ut, ud->random, NULL, &random);
    ut->out[0] = random;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_random_create(&ud.random);

    ut_random_init(ut, ud.random);
    ud.random->min = -0.2;
    ud.random->max = 0.2;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_random_destroy(&ud.random);

    ut_destroy(&ut);
    return 0;
}
