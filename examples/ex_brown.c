#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_brown *brown;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT brown = 0;
    ut_brown_compute(ut, ud->brown, NULL, &brown);
    ut->out[0] = brown;
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 1234567);

    ut_brown_create(&ud.brown);

    ut_brown_init(ut, ud.brown);

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_brown_destroy(&ud.brown);

    ut_destroy(&ut);
    return 0;
}
