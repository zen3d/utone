#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_tblrec *tblrec;
    ut_ftbl *ft; 
    ut_metro *met;
    ut_pluck *plk;
    ut_randi *randi;
    ut_tabread *tr;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT trig, pluck, rand, tr;
    UTFLOAT tick = (ut->pos == 0 ? 1 : 0);
    ut_metro_compute(ut, ud->met, NULL, &trig);
    ut_pluck_compute(ut, ud->plk, &trig, &pluck);
    ut_tblrec_compute(ut, ud->tblrec, &pluck, &tick, NULL);
    ut_randi_compute(ut, ud->randi, NULL, &rand);
    ud->tr->index = rand;
    ut_tabread_compute(ut, ud->tr, NULL, &tr);

    ut->out[0] = tr;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut->len = 44100 * 5;

    /* create */
    ut_tblrec_create(&ud.tblrec);
    ut_ftbl_create(ut, &ud.ft, ut->sr * 0.5);

    ut_metro_create(&ud.met);
    ut_pluck_create(&ud.plk); 
    ut_randi_create(&ud.randi);
    ut_tabread_create(&ud.tr);

    /* init */
    ut_tblrec_init(ut, ud.tblrec, ud.ft);
    ut_metro_init(ut, ud.met);
    ud.met->freq = 2.5;
    ut_pluck_init(ut, ud.plk, 110);
    ud.plk->freq = 440;
    ut_randi_init(ut, ud.randi);
    ut_tabread_init(ut, ud.tr, ud.ft, 1);

    ut_process(ut, &ud, process);

    /* destroy */
    ut_tblrec_destroy(&ud.tblrec);
    ut_ftbl_destroy(&ud.ft);
    ut_metro_destroy(&ud.met);
    ut_pluck_destroy(&ud.plk); 
    ut_randi_destroy(&ud.randi);
    ut_tabread_destroy(&ud.tr);

    ut_destroy(&ut);
    return 0;
}
