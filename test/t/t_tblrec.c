#include "utone.h"
#include "md5.h"
#include "tap.h"
#include "test.h"

typedef struct {
    ut_tblrec *tblrec;
    ut_ftbl *ft; 
    ut_metro *met;
    ut_pluck *plk;
    ut_randi *randi;
    ut_tabread *tr;
} UserData;

int t_tblrec(ut_test *tst, ut_data *ut, const char *hash) 
{
    uint32_t n;
    int fail = 0;
    UTFLOAT trig, pluck, rand, tr, tblrec;
    UTFLOAT tick = (ut->pos == 0 ? 1 : 0);

    ut_srand(ut, 1234567);
    UserData ud;

    ut_tblrec_create(&ud.tblrec);
    ut_ftbl_create(ut, &ud.ft, ut->sr * 0.5);

    ut_metro_create(&ud.met);
    ut_pluck_create(&ud.plk); 
    ut_randi_create(&ud.randi);
    ut_tabread_create(&ud.tr);

    ut_tblrec_init(ut, ud.tblrec, ud.ft);
    ut_metro_init(ut, ud.met);
    ud.met->freq = 2.5;
    ut_pluck_init(ut, ud.plk, 110);
    ud.plk->freq = 440;
    ut_randi_init(ut, ud.randi);
    ut_tabread_init(ut, ud.tr, ud.ft, 1);

    for(n = 0; n < tst->size; n++) {
        trig = 0; 
        pluck = 0;
        rand = 0;
        tr = 0;
        tick = (n == 0 ? 1 : 0);
        tblrec = 0;
        ut_metro_compute(ut, ud.met, NULL, &trig);
        ut_pluck_compute(ut, ud.plk, &trig, &pluck);
        ut_tblrec_compute(ut, ud.tblrec, &pluck, &tick, &tblrec);
        ut_randi_compute(ut, ud.randi, NULL, &rand);
        ud.tr->index = rand;
        ut_tabread_compute(ut, ud.tr, NULL, &tr);
        ut_test_add_sample(tst, tr);
    }

    fail = ut_test_verify(tst, hash);

    ut_tblrec_destroy(&ud.tblrec);
    ut_ftbl_destroy(&ud.ft);
    ut_metro_destroy(&ud.met);
    ut_pluck_destroy(&ud.plk); 
    ut_randi_destroy(&ud.randi);
    ut_tabread_destroy(&ud.tr);


    if(fail) return UT_NOT_OK;
    /* fail by default */
    else return UT_OK;
}
