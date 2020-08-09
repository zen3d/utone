#include <stdlib.h>
#include <math.h>
#include "utone.h"
#include "openlpc.h"

int ut_lpc_create(ut_lpc **lpc)
{
    *lpc = malloc(sizeof(ut_lpc));
    return UT_OK;
}

int ut_lpc_destroy(ut_lpc **lpc)
{
    ut_lpc *plpc;
    plpc = *lpc;
    ut_auxdata_free(&plpc->m_e);
    ut_auxdata_free(&plpc->m_d);
    ut_auxdata_free(&plpc->m_out);
    ut_auxdata_free(&plpc->m_in);
    free(*lpc);
    return UT_OK;
}

int ut_lpc_init(ut_data *ut, ut_lpc *lpc, int framesize)
{
    int i;
    lpc->counter = 0;
    lpc->clock = 0;
    lpc->block = 4;
    lpc->samp = 0;
    lpc->mode = 0;
    lpc->framesize = framesize;
    openlpc_sr(ut->sr / lpc->block);

    ut_auxdata_alloc(&lpc->m_d, openlpc_get_decoder_state_size());
    ut_auxdata_alloc(&lpc->m_e, openlpc_get_encoder_state_size());
    lpc->d = lpc->m_d.ptr;
    lpc->e = lpc->m_e.ptr;

    ut_auxdata_alloc(&lpc->m_in, sizeof(short) * framesize);
    ut_auxdata_alloc(&lpc->m_out, sizeof(short) * framesize);

    lpc->out = lpc->m_out.ptr;
    lpc->in = lpc->m_in.ptr;

    init_openlpc_decoder_state(lpc->d, framesize);
    init_openlpc_encoder_state(lpc->e, framesize);

    for(i = 0; i < framesize; i++) {
        lpc->in[i] = 0;
        lpc->out[i] = 0;
        if(i < 7) lpc->data[i] = 0;
    }
    return UT_OK;
}

int ut_lpc_compute(ut_data *ut, ut_lpc *lpc, UTFLOAT *in, UTFLOAT *out)
{
    int i;


    if(lpc->clock == 0) {
        if(lpc->counter == 0) {
            if(lpc->mode == 0) { 
                openlpc_encode(lpc->in, lpc->data, lpc->e);
            } else {
                for(i = 0; i < 7; i++) {
                    lpc->y[i] = 
                        lpc->smooth*lpc->y[i] + 
                        (1-lpc->smooth)*lpc->ft->tbl[i];
                    lpc->data[i] = 255 * lpc->y[i];
                }
            }
            openlpc_decode(ut, lpc->data, lpc->out, lpc->d);
        }

        if(lpc->mode == 0) lpc->in[lpc->counter] = *in * 32767; 
        lpc->samp = lpc->out[lpc->counter] / 32767.0;

        lpc->counter = (lpc->counter + 1) % lpc->framesize;
    }


    lpc->clock = (lpc->clock + 1) % lpc->block;
    *out = lpc->samp;

    return UT_OK;
}

int ut_lpc_synth(ut_data *ut, ut_lpc *lpc, ut_ftbl *ft)
{
    int i;
    int sr;
    sr = ut->sr;

    sr = sr / 4;
    sr = sr / lpc->framesize;
    lpc->ft = ft;
    lpc->mode = 1;
    for(i = 0; i < 7; i++) lpc->y[i] = 0;
    lpc->smooth = exp(-1.0 / (0.01 * sr));
    return UT_OK;
}
