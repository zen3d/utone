sptbl["waveset"] = {

    files = {
        module = "waveset.c",
        header = "waveset.h",
        example = "ex_waveset.c",
    },

    func = {
        create = "ut_waveset_create",
        destroy = "ut_waveset_destroy",
        init = "ut_waveset_init",
        compute = "ut_waveset_compute",
    },

    params = {
        mandatory = {
            {
                name = "ilen",
                type = "UTFLOAT",
                description = "Length of buffer (in seconds).",
                default = 1.0 
            }
        },

        optional = {
            {
                name = "rep",
                type = "UTFLOAT",
                description = "Number of repeats.",
                default = 1.5
            },
        }
    },

    modtype = "module",

    description = [[Simple Time-stretching from repeating wavecyles
This module looks for zero-crossings and repeats them by a integer factor.
While a crude means for time stretching, it is a very aesthetically pleasing
effect to use on sounds and often produces a "wet" sound.

The waveset algorithm was originally created by Trevor Wishart for the Composer
Desktop Project (CDP), and was then ported to Csound. 
]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "input",
            description = "Signal input."
        },
    },

    outputs = {
        {
            name = "out",
            description = "signal output."
        },
    }

}
