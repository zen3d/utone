How to Create a Soundpipe Module
================================

Creating new modules in Soundpipe is a relatively straightforward process.

For this tutorial, we are going to create a gain module called "gain". 

## Bootstrapping

Soundpipe has a script that automatically creates the necessary template files
needed to create a module. 

This can be invoked with "make" with the following command:

make bootstrap MODULE_NAME="gain"

Make sure the module name you choose is unique.

If successful, this script will create 4 boiler plate files:
- modules/gain.c: the main c code. 
- h/gain.h: the header file
- examples/ex_gain.c: an example file utilizing gain
- modules/data/gain.lua: metadata for gain, used to create a doc page

A fully implemented module file will have these components:

## The Header File

Typically, the only thing here you would need to implement is the data struct 
(empty by default). However, it is okay to tack on variables to the end of the
init function if you need to do things like create delay lines. 

```
typedef struct {
    UTFLOAT gain;
} ut_gain;
```

## The Module File

```
int ut_gain_init(ut_data *sp, ut_gain *p)
{
    p->gain = 0;
    return UT_OK;
}

int ut_gain_compute(ut_data *sp, ut_gain *p, UTFLOAT *in, UTFLOAT *out)
{
    *out = *in * p->gain;
    return UT_OK;
}
```

## The example

```
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utone.h"

typedef struct {
    ut_gain *gain;
    ut_osc *osc;
    ut_ftbl *ft; 
} UserData;

void process(ut_data *sp, void *udata) {
    UserData *ud = udata;
    UTFLOAT osc = 0, gain = 0;
    ut_osc_compute(sp, ud->osc, NULL, &osc);
    ut_gain_compute(sp, ud->gain, &osc, &gain);
    sp->out[0] = gain;
}

int main() {
    srand(1234567);
    UserData ud;
    ut_data *sp;
    ut_create(&sp);

    ut_gain_create(&ud.gain);
    ut_osc_create(&ud.osc);
    ut_ftbl_create(sp, &ud.ft, 2048);

    ud.gain->gain = 0.3;

    ut_gain_init(sp, ud.gain);
    ut_gen_sine(sp, ud.ft);
    ut_osc_init(sp, ud.osc, ud.ft);

    sp->len = 44100 * 5;
    ut_process(sp, &ud, process);

    ut_gain_destroy(&ud.gain);
    ut_ftbl_destroy(&ud.ft);
    ut_osc_destroy(&ud.osc);

    ut_destroy(&sp);
    return 0;
}
```

## Metadata / Documentation

```
sptbl["gain"] = {

    files = { 
        module = "gain.c",
        header = "gain.h",
        example = "ex_gain.c",
    },
    
    func = {
        create = "ut_gain_create",
        destroy = "ut_gain_destroy",
        init = "ut_gain_init",
        compute = "ut_gain_compute"
    },
    
    params = {
        optional = {
            {
                name = "gain",
                type = "UTFLOAT",
                description = "Sets the gain",
                default = 0
            },
        }
    },
    
    modtype = "module",
    
    description = [[Scale an incoming signal.]], 
    
    ninputs = 1,
    noutputs = 1,
    
    inputs = { 
        {
            name = "input",
            description = "this is the audio input for a made up plugin."
        },
    },
    
    outputs = {
        {
            name = "out",
            description = "Signal output",
        },
    }

}
```

## Adding to Soundpipe
To add your module to Soundpipe, run the following command:

add to config.mk
compile

## Buffers in Soundpipe

Coming soon!

## Using ftables in Soundpipe

Coming soon!

## Creating GEN routines in Soundpipe

Coming soon! 


