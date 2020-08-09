#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_line *line;
    ut_osc *osc;
    ut_ftbl *ft; 
    ut_dmetro *dm;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, line = 0, dm = 0;
    ut_dmetro_compute(ut, ud->dm, NULL, &dm);
    ut_line_compute(ut, ud->line, &dm, &line);
    ud->osc->freq = line;
    ut_osc_compute(ut, ud->osc, NULL, &osc);
    ut->out[0] = osc;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_line_create(&ud.line);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_dmetro_create(&ud.dm);

    ut_line_init(ut, ud.line);
    ud.line->a = 100;
    ud.line->dur = 1;
    ud.line->b = 400;
    ut_gen_sine(ut, ud.ft);
    ut_osc_init(ut, ud.osc, ud.ft, 0);
    ut_dmetro_init(ut, ud.dm);
    ud.dm->time = 2;

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_line_destroy(&ud.line);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);
    ut_dmetro_destroy(&ud.dm);

    ut_destroy(&ut);
    return 0;
}
