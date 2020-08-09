name = arg[1]
sptbl = {}

dofile ("../../ut_dict.lua")

header=[[
#include <stdlib.h>
#include <stdio.h>
#include "utone.h"
#include "config.h"

int main() {
    ut_data *sp;
    ut_create(&sp);
    ut_srand(sp, 12345);
    sp->sr = SR;
    sp->len = sp->sr * LEN;
    uint32_t t, u;
    UTFLOAT in = 0, out = 0;
]]

compute=[[
    ut_FOO *unit[NUM];

    for(u = 0; u < NUM; u++) { 
        ut_FOO_create(&unit[u]);
        ut_FOO_init(sp, unit[u]);
    }

    for(t = 0; t < sp->len; t++) {
        for(u = 0; u < NUM; u++) ut_FOO_compute(sp, unit[u], &in, &out);
    }

    for(u = 0; u < NUM; u++) ut_FOO_destroy(&unit[u]);
]]


footer=[[
    ut_destroy(&sp);
    return 0;
}
]]

compute = string.gsub(compute, "FOO", name)

print(header)
print(compute)
print(footer)
