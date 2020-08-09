#include <stdlib.h>
#include "utone.h"

typedef struct {
    ut_diskin *wav;
    ut_lpc *lpc;
} user_data;

static void process(ut_data *ut, void *ud)
{
    user_data *dt;
    UTFLOAT diskin;
    UTFLOAT out;
    dt = ud;

    ut_diskin_compute(ut, dt->wav, NULL, &diskin);
    ut_lpc_compute(ut, dt->lpc, &diskin, &out);


    ut_out(ut, 0, out);
}

int main(int argc, char **argv)
{
    user_data dt;
    ut_data *ut;

    ut_create(&ut);
    ut->sr = 44100;
    ut->len = ut->sr * 8;

    ut_lpc_create(&dt.lpc);
    ut_lpc_init(ut, dt.lpc, 512);

    ut_diskin_create(&dt.wav);
    ut_diskin_init(ut, dt.wav, "oneart.wav");


    ut_process(ut, &dt, process);
    ut_diskin_destroy(&dt.wav);
    ut_lpc_destroy(&dt.lpc);
    ut_destroy(&ut);
    return 0;
}
