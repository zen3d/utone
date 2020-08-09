#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_uta *uta;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT uta = 0;
    ut_uta_compute(ut, ud->uta, NULL, &uta);
    ut->out[0] = uta;
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 1234567);

    ut_uta_create(&ud.uta);

    ut_uta_init(ut, ud.uta, "oneart.uta");

    ut->len = 44100 * 10;
    ut_process(ut, &ud, process);

    ut_uta_destroy(&ud.uta);

    ut_destroy(&ut);
    return 0;
}
