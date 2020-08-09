sptbl["biquad"] = {

    files = {
        module = "biquad.c",
        header = "biquad.h",
        --example = "ex_tone.c",
    },

    func = {
        create = "ut_biquad_create",
        destroy = "ut_biquad_destroy",
        init = "ut_biquad_init",
        compute = "ut_biquad_compute",
    },

    params = {
        optional = {
            {
                name = "b0",
                type = "UTFLOAT",
                description = "biquad coefficient.",
                default = 0
            },
            {
                name = "b1",
                type = "UTFLOAT",
                description = "biquad coefficient.",
                default = 0
            },
            {
                name = "b2",
                type = "UTFLOAT",
                description = "biquad coefficient.",
                default = 0
            },
            {
                name = "a0",
                type = "UTFLOAT",
                description = "biquad coefficient.",
                default = 0
            },
            {
                name = "a1",
                type = "UTFLOAT",
                description = "biquad coefficient.",
                default = 0
            },
            {
                name = "a2",
                type = "UTFLOAT",
                description = "biquad coefficient.",
                default = 0
            }
        }
    },

    modtype = "module",

    description = [[A sweepable biquadratic general purpose filter

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
            description = "Signal output."
        },
    }

}
