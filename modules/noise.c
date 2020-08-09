#include <math.h>
#include <stdlib.h>
#include "utone.h"

int ut_noise_create(ut_noise **ns)
{
    *ns = malloc(sizeof(ut_noise));
    return UT_OK;
}

int ut_noise_init(ut_data *ut, ut_noise *ns)
{
    ns->amp = 1.0;
    return UT_OK;
}

int ut_noise_compute(ut_data *ut, ut_noise *ns, UTFLOAT *in, UTFLOAT *out)
{
    *out = ((ut_rand(ut) % UT_RANDMAX) / (UT_RANDMAX * 1.0));
    *out = (*out * 2) - 1;
    *out *= ns->amp;
    return UT_OK;
}

int ut_noise_destroy(ut_noise **ns)
{
    free(*ns);
    return UT_OK;
}
