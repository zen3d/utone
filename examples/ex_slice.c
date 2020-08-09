/*
 * This is a dummy example.
 * Please implement a small and simple working example of your module, and then
 * remove this header.
 * Don't be clever.
 * Bonus points for musicality. 
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_slice *slice;
    ut_ftbl *vals; 
    ut_ftbl *buf; 
    ut_dmetro *met;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT slice = 0;
    UTFLOAT dm = 0;
    ut_dmetro_compute(ut, ud->met, NULL, &dm);
    ud->slice->id = 2;
    ut_slice_compute(ut, ud->slice, &dm, &slice);
    ut_out(ut, 0, slice);
}

int main() {
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 1234567);

    ut_slice_create(&ud.slice);
    ut_ftbl_create(ut, &ud.vals, 1);
    ut_ftbl_loadfile(ut, &ud.buf, "oneart.wav");
    ut_dmetro_create(&ud.met);

    ut_gen_vals(ut, ud.vals, 
    "6770 96139 159104 228847");

    ut_slice_init(ut, ud.slice, ud.vals, ud.buf);
    ut_dmetro_init(ut, ud.met);
    ud.met->time = 0.75;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_slice_destroy(&ud.slice);
    ut_dmetro_destroy(&ud.met);
    ut_ftbl_destroy(&ud.buf);
    ut_ftbl_destroy(&ud.vals);

    ut_destroy(&ut);
    return 0;
}
