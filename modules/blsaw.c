/*
 * Saw
 *
 * This code was generated by Faust. It utilizes the saw2 Faust
 * module coded by Julius Smith. See oscillator.lib for more details.
 *
 */

#include <stdlib.h>
#include <math.h>
#include "utone.h"
#include "CUI.h"

#define max(a,b) ((a < b) ? b : a)
#define min(a,b) ((a < b) ? a : b)

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

static float faustpower2_f(float value) {
	return (value * value);

}

typedef struct {

	float fRec0[2];
	float fVec0[2];
	float fVec1[2];
	int fSamplingFreq;
	int iConst0;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	float fConst1;
	float fConst2;
} blsaw;

blsaw* newblsaw() {
	blsaw* dsp = (blsaw*)malloc(sizeof(blsaw));
	return dsp;
}

void deleteblsaw(blsaw* dsp) {
	free(dsp);
}

void instanceInitblsaw(blsaw* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->iConst0 = min(192000, max(1, dsp->fSamplingFreq));
	dsp->fHslider0 = (FAUSTFLOAT)1.;
	dsp->fHslider1 = (FAUSTFLOAT)440.;
	dsp->fConst1 = (float)dsp->iConst0;
	dsp->fConst2 = (2.f / dsp->fConst1);
	/* C99 loop */
	{
		int i0;
		for (i0 = 0; (i0 < 2); i0 = (i0 + 1)) {
			dsp->fRec0[i0] = 0.f;

		}

	}
	/* C99 loop */
	{
		int i1;
		for (i1 = 0; (i1 < 2); i1 = (i1 + 1)) {
			dsp->fVec0[i1] = 0.f;

		}

	}
	/* C99 loop */
	{
		int i2;
		for (i2 = 0; (i2 < 2); i2 = (i2 + 1)) {
			dsp->fVec1[i2] = 0.f;

		}

	}

}

void initblsaw(blsaw* dsp, int samplingFreq) {
	instanceInitblsaw(dsp, samplingFreq);
}

void buildUserInterfaceblsaw(blsaw* dsp, UIGlue* interface) {
	interface->addHorizontalSlider(interface->uiInterface, "freq", &dsp->fHslider1, 440.f, 0.f, 20000.f, 0.0001f);
	interface->addHorizontalSlider(interface->uiInterface, "amp", &dsp->fHslider0, 1.f, 0.f, 1.f, 0.0001f);
}

void computeblsaw(blsaw* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* output0 = outputs[0];
	float fSlow0 = (float)dsp->fHslider1;
	float fSlow1 = ((float)dsp->iConst0 * ((float)dsp->fHslider0 / fSlow0));
	float fSlow2 = (dsp->fConst2 * fSlow0);
	float fSlow3 = (dsp->fConst1 / fSlow0);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fRec0[0] = fmod((1.f + dsp->fRec0[1]), fSlow3);
			float fTemp0 = faustpower2_f(((fSlow2 * dsp->fRec0[0]) - 1.f));
			dsp->fVec0[0] = fTemp0;
			dsp->fVec1[0] = 0.25f;
			output0[i] = (FAUSTFLOAT)(fSlow1 * ((fTemp0 - dsp->fVec0[1]) * dsp->fVec1[1]));
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fVec0[1] = dsp->fVec0[0];
			dsp->fVec1[1] = dsp->fVec1[0];

		}

	}

}


static void addHorizontalSlider(void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
{
    ut_blsaw *p = ui_interface;
    p->args[p->argpos] = zone;
    p->argpos++;
}

int ut_blsaw_create(ut_blsaw **p)
{
    *p = malloc(sizeof(ut_blsaw));
    return UT_OK;
}

int ut_blsaw_destroy(ut_blsaw **p)
{
    ut_blsaw *pp = *p;
    blsaw *dsp = pp->ud;
    deleteblsaw (dsp);
    free(*p);
    return UT_OK;
}

int ut_blsaw_init(ut_data *ut, ut_blsaw *p)
{
    blsaw *dsp = newblsaw();
    UIGlue UI;
    p->argpos = 0;
    UI.addHorizontalSlider= addHorizontalSlider;
    UI.uiInterface = p;
    buildUserInterfaceblsaw(dsp, &UI);
    initblsaw(dsp, ut->sr);


    p->freq = p->args[0];
    p->amp = p->args[1];

    p->ud = dsp;
    return UT_OK;
}

int ut_blsaw_compute(ut_data *ut, ut_blsaw *p, UTFLOAT *in, UTFLOAT *out)
{

    blsaw *dsp = p->ud;
    UTFLOAT out1 = 0;
    UTFLOAT *faust_out[] = {&out1};
    UTFLOAT *faust_in[] = {in};
    computeblsaw(dsp, 1, faust_in, faust_out);

    *out = out1;
    return UT_OK;
}
