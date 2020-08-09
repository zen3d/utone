#include "utone.h"

typedef struct {
    uint16_t counter;
    uint16_t t;
    UTFLOAT out;
} UserData;

void process(ut_data *ut, void *udata) 
{
    UserData *ud = udata;
    if(ud->counter == 0) {
        uint16_t t = ud->t;

        ud->out = 
            (UTFLOAT)((t*(((t>>12)|(t>>8))&(63&(t>>4)))) & 0xFF);
        ud->out /= 0xFF;
        ud->out -= 0.5;
        ud->out *= 0.3;
        ud->t++;
    }
    ut->out[0] = ud->out;
    ud->counter++;
    ud->counter %= 10;
}

int main()
{
    UserData ud;
    ut_data *ut;
    ud.counter = 0;
    ud.t = 0;
    ut_create(&ut);
    ut->len = 44100 * 15;
    ut_process(ut, &ud, process);
    ut_destroy(&ut);
    return 0;
}
