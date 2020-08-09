#include <stdlib.h>
#include <math.h>
#include "utone.h"

#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef dB
/* if below -100dB, set to -100dB to prevent taking log of zero */
#define dB(x) 20.0 * ((x) > 0.00001 ? log10(x) : log10(0.00001))
#endif

#ifndef dB2lin
#define dB2lin(x)           pow( 10.0, (x) / 20.0 )
#endif

int ut_peaklim_create(ut_peaklim **p)
{
    *p = malloc(sizeof(ut_peaklim));
    return UT_OK;
}

int ut_peaklim_destroy(ut_peaklim **p)
{
    free(*p);
    return UT_OK;
}

int ut_peaklim_init(ut_data *ut, ut_peaklim *p)
{
    p->a1_r = 0;
    p->b0_r = 1;
    p->a1_a = 0;
    p->b0_a = 1;
    p->atk = 0.1;
    p->rel = 0.1;
    p->patk = -100;
    p->prel = -100;
    p->level = 0;
    return UT_OK;
}

int ut_peaklim_compute(ut_data *ut, ut_peaklim *p, UTFLOAT *in, UTFLOAT *out)
{

    UTFLOAT db_gain = 0;
    UTFLOAT gain = 0;

    /* change coefficients, if needed */

    if(p->patk != p->atk) {
        p->patk = p->atk;
		p->a1_a = exp( -1.0 / ( p->rel * ut->sr ) );
		p->b0_a = 1 - p->a1_a;
    }

    if(p->prel != p->rel) {
        p->prel = p->rel;
		p->a1_r = exp( -1.0 / ( p->rel * ut->sr ) );
		p->b0_r = 1 - p->a1_r;
    }

    
    if ( fabs(*in) > p->level)
        p->level += p->b0_a * ( fabs(*in) - p->level);
    else
        p->level += p->b0_r * ( fabs(*in) - p->level);

    db_gain = min(0.0, dB(dB2lin(p->thresh)/p->level));
    gain = dB2lin(db_gain);		

    *out = *in * gain;

    return UT_OK;
}
