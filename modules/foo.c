/*
 * Foo
 * 
 * This is a dummy module. It doesn't do much.
 * Feel free to use this as a boilerplate template.
 * 
 */

#include <stdlib.h>
#include "utone.h"

int ut_foo_create(ut_foo **p)
{
    *p = malloc(sizeof(ut_foo));
    return UT_OK;
}

int ut_foo_destroy(ut_foo **p)
{
    free(*p);
    return UT_OK;
}

int ut_foo_init(ut_data *ut, ut_foo *p)
{
    /* Initalize variables here. */
    p->bar = 123;
    return UT_OK;
}

int ut_foo_compute(ut_data *ut, ut_foo *p, UTFLOAT *in, UTFLOAT *out)
{
    /* Send the signal's input to the output */
    *out = *in;
    return UT_OK;
}
