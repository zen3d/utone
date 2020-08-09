/*
 * This module reads from standard input, and writes it to a wave file.
 * 
 * To write 5 seconds of white noise:
 *
 * cat /dev/urandom | ./ex_in.bin
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_in *in;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT in = 0;
    ut_in_compute(ut, ud->in, NULL, &in);
    ut->out[0] = in;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_in_create(&ud.in);

    ut_in_init(ut, ud.in);

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_in_destroy(&ud.in);

    ut_destroy(&ut);
    return 0;
}
