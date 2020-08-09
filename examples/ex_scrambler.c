#include "utone.h"

typedef struct {
    ut_ftbl *src;
    ut_ftbl *dest;
} UserData;

static void process(ut_data *ut, void *userdata)
{
    UserData *ud = userdata;
    ut_out(ut, 0, ud->dest->tbl[ut->pos]);
}

int main()
{
    ut_data *ut;
    UserData ud;
    ut_create(&ut);
    ut_srand(ut, 12345);
    ut_ftbl_loadfile(ut, &ud.src, "oneart.wav");
    ut_gen_scrambler(ut, ud.src, &ud.dest);
    ut->len = ud.src->size;
    ut_process(ut, &ud, process);
    ut_ftbl_destroy(&ud.src);
    ut_ftbl_destroy(&ud.dest);
    ut_destroy(&ut);
    return 0;
}
