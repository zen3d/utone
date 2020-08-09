#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_metro *met;
    ut_ftbl *ft; 
    ut_tabread *tab;
    ut_phasor *phs;
    ut_tenv *tenv;
    ut_pdhalf *pdhalf;
    ut_scale *scl;
    ut_tseq *ts;
    ut_ftbl *seq; 
} UserData;

void process(ut_data *ut, void *udata) 
{
    UserData *ud = udata;
    UTFLOAT met = 0;
    UTFLOAT tenv = 0;
    UTFLOAT phs = 0;
    UTFLOAT pd = 0;
    UTFLOAT tr = 0;
    UTFLOAT amt = 0;
    UTFLOAT rev = 0;
    UTFLOAT frq = 0;

    ut_metro_compute(ut, ud->met, NULL, &met);
    ut_tenv_compute(ut, ud->tenv, &met, &tenv);
    ut_tseq_compute(ut, ud->ts, &met, &frq);
    frq = ut_midi2cps(frq);
    ud->phs->freq = frq;
    ut_phasor_compute(ut, ud->phs, NULL, &phs);
    rev = 1 - tenv;
    ut_scale_compute(ut, ud->scl, &rev, &amt);
    ud->pdhalf->amount = amt;
    ut_pdhalf_compute(ut, ud->pdhalf, &phs, &pd);
    ud->tab->index = pd;
    ut_tabread_compute(ut, ud->tab, NULL, &tr);

    ut_out(ut, 0, tr * tenv);

}

int main() 
{
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_srand(ut, 1234567);

    ut_pdhalf_create(&ud.pdhalf);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_gen_sine(ut, ud.ft);
    ut_metro_create(&ud.met);

    ut_tabread_create(&ud.tab);
    ut_tenv_create(&ud.tenv);
    ut_phasor_create(&ud.phs);
    ut_scale_create(&ud.scl);
    ut_ftbl_create(ut, &ud.seq, 1);
    ut_gen_vals(ut, ud.seq, "62 67 69 72");
    ut_tseq_create(&ud.ts);


    ut_pdhalf_init(ut, ud.pdhalf);
    ut_tabread_init(ut, ud.tab, ud.ft, 1);
    ut_phasor_init(ut, ud.phs, 0);
    ud.phs->freq = 440;
    ut_tenv_init(ut, ud.tenv);
    ud.tenv->atk = 0.001;
    ud.tenv->hold = 0.01;
    ud.tenv->rel = 0.2;
    ut_metro_init(ut, ud.met);
    ud.met->freq = 8;
    ut_scale_init(ut, ud.scl);
    ud.scl->min = -0.8;
    ud.scl->max = 0;
    ut_tseq_init(ut, ud.ts, ud.seq);


    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_pdhalf_destroy(&ud.pdhalf);
    ut_ftbl_destroy(&ud.ft);
    ut_tabread_destroy(&ud.tab);
    ut_phasor_destroy(&ud.phs);
    ut_tenv_destroy(&ud.tenv);
    ut_metro_destroy(&ud.met);
    ut_scale_destroy(&ud.scl);
    ut_tseq_destroy(&ud.ts);
    ut_ftbl_destroy(&ud.seq);

    ut_destroy(&ut);
    return 0;
}
