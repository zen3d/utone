#include "utone.h"

typedef struct {
    ut_allpass *ap;
    ut_tenv *env;
    ut_noise *nz;
} UserData;

void process(ut_data *ut, void *udata) {
    UserData *ud = udata;
    UTFLOAT tick = 0, env = 0, noise = 0, allpass = 0;

    tick = (ut->pos == 0) ? 1 : 0;
    ut_tenv_compute(ut, ud->env, &tick, &env);
    ut_noise_compute(ut, ud->nz, NULL, &noise);
    noise *= env * 0.5;
    ut_allpass_compute(ut, ud->ap, &noise, &allpass);

    ut->out[0] = allpass;
}


int main()
{
    UserData ud;
    ut_data *ut;
    ut_create(&ut);

    ut_allpass_create(&ud.ap);
    ut_tenv_create(&ud.env);
    ut_noise_create(&ud.nz);

    ut_allpass_init(ut, ud.ap, 0.1);
    ut_tenv_init(ut, ud.env);
    ud.env->atk = 0.001;
    ud.env->hold = 0.00;
    ud.env->rel =  0.1;

    ut_noise_init(ut, ud.nz);

    ut->len = 44100 * 5;
    ut_process(ut, &ud, process);

    ut_noise_destroy(&ud.nz);
    ut_tenv_destroy(&ud.env);
    ut_allpass_destroy(&ud.ap);

    ut_destroy(&ut);
    return 0;
}
