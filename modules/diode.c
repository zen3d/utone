/*
 * Diode
 * 
 * Based on Will Pirkle's Diode Ladder filter design. 
 * Code adapted from the CCRMA Chugin WPDiodeLadder
 * 
 */

#include <stdlib.h>
#include <math.h>
#include "utone.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int ut_diode_create(ut_diode **p)
{
    *p = malloc(sizeof(ut_diode));
    return UT_OK;
}

int ut_diode_destroy(ut_diode **p)
{
    free(*p);
    return UT_OK;
}

static UTFLOAT ut_diode_opva_fdbk_out(ut_data *ut, ut_diode *p, int filt)
{
    return p->opva_beta[filt] * 
        (p->opva_z1[filt] + p->opva_fdbk[filt] * p->opva_delta[filt]);
}

static UTFLOAT ut_diode_opva_compute(ut_data *ut, ut_diode *p, UTFLOAT in, int filt)
{
    /*
	double x_in = (xn*m_dGamma + m_dFeedback + m_dEpsilon*getFeedbackOutput());
	
	double vn = (m_da0*x_in - m_dZ1)*m_dAlpha;
	double out = vn + m_dZ1;
	m_dZ1 = vn + out;
    */

	/* m_dBeta*(m_dZ1 + m_dFeedback*m_dDelta); */

	UTFLOAT x_in = (in*p->opva_gamma[filt]
        + p->opva_fdbk[filt]
        + p->opva_eps[filt] * ut_diode_opva_fdbk_out(ut, p, filt));
	UTFLOAT vn = (p->opva_a0[filt]*x_in - 
        p->opva_z1[filt])*p->opva_alpha[filt];
	UTFLOAT out = vn + p->opva_z1[filt];
	p->opva_z1[filt] = vn + out;
    return out;
}

static void ut_diode_update(ut_data *ut, ut_diode *p)
{
	/* calculate alphas */
	UTFLOAT G1, G2, G3, G4;
	UTFLOAT wd = 2*M_PI*p->freq;          
	UTFLOAT T  = 1/(UTFLOAT)ut->sr;             
	UTFLOAT wa = (2/T)*tan(wd*T/2); 
	UTFLOAT g = wa*T/2;  
    int i;

    /* Big G's */
	G4 = 0.5*g/(1.0 + g);
	G3 = 0.5*g/(1.0 + g - 0.5*g*G4);
	G2 = 0.5*g/(1.0 + g - 0.5*g*G3);
	G1 = g/(1.0 + g - g*G2);

    /* big G value gamma */
    p->gamma  = G4*G3*G2*G1;
	
    p->SG[0] =  G4*G3*G2; 
	p->SG[1] =  G4*G3; 
	p->SG[2] =  G4; 
	p->SG[3] =  1.0; 

	/* set alphas */
    for(i = 0; i < 4; i++) p->opva_alpha[i] = g/(1.0 + g);
	
    /* set betas */
    p->opva_beta[0] = 1.0/(1.0 + g - g*G2);
	p->opva_beta[1] = 1.0/(1.0 + g - 0.5*g*G3);
	p->opva_beta[2] = 1.0/(1.0 + g - 0.5*g*G4);
	p->opva_beta[3] = 1.0/(1.0 + g);

	/* set gammas */
	p->opva_gamma[0] = 1.0 + G1*G2;
	p->opva_gamma[1] = 1.0 + G2*G3;
	p->opva_gamma[2] = 1.0 + G3*G4;

    /* set deltas */
	p->opva_delta[0] = g;
	p->opva_delta[1] = 0.5*g;
	p->opva_delta[2] = 0.5*g;

    /* set epsilons */
	p->opva_eps[0] = G2;
	p->opva_eps[1] = G3;
	p->opva_eps[2] = G4;
}

int ut_diode_init(ut_data *ut, ut_diode *p)
{
    int i;
    /* initialize the 4 one-pole VA filters */

    for(i = 0; i < 4; i++) {
        p->opva_alpha[i] = 1.0;		
        p->opva_beta[i] = -1.0;		
        p->opva_gamma[i] = 1.0;
        p->opva_delta[i] = 0.0;
        p->opva_eps[i] = 1.0;
        p->opva_fdbk[i] = 0.0;
        p->opva_a0[i] = 1.0;
        p->opva_z1[i] = 0.0;

        p->SG[i] = 0.0;
    }

	p->gamma = 0.0;
	p->K = 0.0;

	/* Filter coeffs that are constant */
	/* set a0s */
    p->opva_a0[0] = 1.0;
    p->opva_a0[1] = 0.5;
    p->opva_a0[2] = 0.5;
    p->opva_a0[3] = 0.5;

	/* last LPF has no feedback path */
    p->opva_gamma[3] = 1.0;
    p->opva_delta[3] = 0.0;
    p->opva_eps[3] = 0.0;
    p->opva_fdbk[3] = 0.0;

    /* default cutoff to 1000hz */
    p->freq = 1000;
    p->res = 0;
    /* update filter coefs */

    ut_diode_update(ut, p);
    return UT_OK;
}

int ut_diode_compute(ut_data *ut, ut_diode *p, UTFLOAT *in, UTFLOAT *out)
{
    int i;
    UTFLOAT sigma;
    UTFLOAT un;
    UTFLOAT tmp = 0.0;

    /* update filter coefficients */
    p->K = p->res * 17;
    ut_diode_update(ut, p);

    p->opva_fdbk[2] = ut_diode_opva_fdbk_out(ut, p, 3);
    p->opva_fdbk[1] = ut_diode_opva_fdbk_out(ut, p, 2);
    p->opva_fdbk[0] = ut_diode_opva_fdbk_out(ut, p, 1);

    sigma = 
        p->SG[0] * ut_diode_opva_fdbk_out(ut, p, 0) +
        p->SG[1] * ut_diode_opva_fdbk_out(ut, p, 1) +
        p->SG[2] * ut_diode_opva_fdbk_out(ut, p, 2) +
        p->SG[3] * ut_diode_opva_fdbk_out(ut, p, 3);

    un = (*in - p->K * sigma) / (1 + p->K * p->gamma);
    tmp = un;
    for(i = 0; i < 4; i++) {
        tmp = ut_diode_opva_compute(ut, p, tmp, i);
    }
    *out = tmp;
    return UT_OK;
}
