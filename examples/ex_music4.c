#include <stdio.h>
#include "utone.h"

#define NOTEDUR 8000

typedef struct{
    ut_posc3 *posc[8];
    ut_tenv *tenv[8];
    ut_revsc *rev;
    ut_ftbl *ft;
}UserData;

void make_note(ut_data *ut, ut_tenv *tenv, ut_posc3 *posc3, unsigned long counter, unsigned long clock, UTFLOAT *output)
{
    unsigned long count = counter % clock;
    UTFLOAT env = 0, osc = 0;
    UTFLOAT tick = (count == 0) ? 1 : 0;
    ut_tenv_compute(ut, tenv, &tick, &env);
    ut_posc3_compute(ut, posc3, NULL, &osc);
    *output = osc * env;
}
void write_music(ut_data *ut, void *ud)
{
    UserData *udp = ud;
    UTFLOAT out[8];
    UTFLOAT mix, verb, foo;
    for(int i = 0; i < 8; i++) {
        make_note(ut, udp->tenv[i], udp->posc[i], ut->pos, ((i * NOTEDUR) + NOTEDUR), &out[i]);
    }
    mix = (out[0] * 0.2) + (out[1] * 0.2) + (out[2] * 0.2) + (out[3] * 0.2) + (out[4] * 0.2) + (out[5] * 0.2)
       + (out[6] * 0.2) +  (out[7] * 0.2);
    ut_revsc_compute(ut, udp->rev, &mix, &mix, &verb, &foo);
    ut->out[0] = mix + (verb * 0.2);
}

int main()
{
    UserData ud;
    ut_data *ut;
    ut_create(&ut);
    ut_ftbl_create(ut, &ud.ft, 4096);
    for(int i = 0; i < 8; i++) ut_posc3_create(&ud.posc[i]);
    for(int i = 0; i < 8; i++) ut_tenv_create(&ud.tenv[i]);
    ut_revsc_create(&ud.rev);
    ut_gen_sine(ut, ud.ft);

    for(int i = 0; i < 8; i++) {
        ut_tenv_init(ut, ud.tenv[i]);
        ud.tenv[i]->atk = 0.01;
        ud.tenv[i]->hold = 0.1;
        ud.tenv[i]->rel =  0.1;
    }
    for(int i = 0; i < 8; i++) ut_posc3_init(ut, ud.posc[i], ud.ft);
    ud.posc[0]->freq = ut_midi2cps(48);
    ud.posc[1]->freq = ut_midi2cps(52);
    ud.posc[2]->freq = ut_midi2cps(59);
    ud.posc[3]->freq = ut_midi2cps(62);
    ud.posc[4]->freq = ut_midi2cps(72);
    ud.posc[5]->freq = ut_midi2cps(71);
    ud.posc[6]->freq = ut_midi2cps(69);
    ud.posc[7]->freq = ut_midi2cps(66);

    ut_revsc_init(ut, ud.rev);

    ut->len = 44100 * 20;
    ut_process(ut, &ud, write_music);

    for(int i = 0; i < 8; i++) ut_posc3_destroy(&ud.posc[i]);
    for(int i = 0; i < 8; i++) ut_tenv_destroy(&ud.tenv[i]);
    ut_revsc_destroy(&ud.rev);
    ut_ftbl_destroy(&ud.ft);
    ut_destroy(&ut);
    return 0;
}
