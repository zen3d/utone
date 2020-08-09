#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_pinknoise *ns;
} UserData;

void write_pinknoise(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT out = 0;
    ut_pinknoise_compute(ut, ud->ns, NULL, &out);
    ut_out(ut, 0, out);
}

int main() {
    srand(time(NULL));
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_pinknoise_create(&ud.ns);
    ut_pinknoise_init(ut, ud.ns);
    ut->len = 44100 * 5;
    ut_process(ut, &ud, write_pinknoise);
    ut_pinknoise_destroy(&ud.ns);
    ut_destroy(&ut);
    return 0;
}
