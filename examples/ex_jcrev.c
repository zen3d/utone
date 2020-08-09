#include "utone.h"

typedef struct {
    ut_fosc *osc;
    ut_ftbl *ft; 
    ut_jcrev *dsp;
    int counter;
} UserData;

void process(ut_data *ut, void *udata)
{
    UserData *ud = udata;
    UTFLOAT in = 0, out = 0;
    
    if(ud->counter == 0){
        ud->osc->freq = 500 + ut_rand(ut) % 2000;
    }

    ut_fosc_compute(ut, ud->osc, NULL, &in);
    ut_jcrev_compute(ut, ud->dsp, &in, &out);

    ut->out[0] = out;
    ud->counter = (ud->counter + 1) % 4410;
}

int main()
{
    ut_data *ut;
    UserData ud;

    ut_create(&ut);
    ut_srand(ut, 123456);
    ut_jcrev_create(&ud.dsp);
    ut_ftbl_create(ut, &ud.ft, 2048);
    ut_fosc_create(&ud.osc);

    ut_jcrev_init(ut, ud.dsp);
    ud.counter = 0;
    ut_gen_sine(ut, ud.ft);
    ut_fosc_init(ut, ud.osc, ud.ft);
    ud.osc->freq = 500;

    ut_process(ut, &ud, process);

    ut_jcrev_destroy(&ud.dsp);
    ut_ftbl_destroy(&ud.ft);
    ut_fosc_destroy(&ud.osc);
    
    ut_destroy(&ut);
}
