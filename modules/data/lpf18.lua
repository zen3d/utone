sptbl["lpf18"] = {

    files = {
        module = "lpf18.c",
        header = "lpf18.h",
        example = "ex_lpf18.c",
    },

    func = {
        create = "ut_lpf18_create",
        destroy = "ut_lpf18_destroy",
        init = "ut_lpf18_init",
        compute = "ut_lpf18_compute",
    },

    params = {
        optional = {
            {
                name = "cutoff",
                type = "UTFLOAT",
                description = "Filter cutoff frequency, in Hertz",
                default = 1000
            },
            {
                name = "res",
                type = "UTFLOAT",
                description ="Resonance. Expects a value in the range 0-1. A value of 1.0 will self oscillate at the cutoff frequency.",
                default = 0.8
            },
            {
                name = "dist",
                type = "UTFLOAT",
                description ="Distortion amount.",
                default = 2
            },
        }
    },

    modtype = "module",

    description = [[3-pole (18 db/oct slope) Low-Pass filter with resonance and tanh distortion]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "in",
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
