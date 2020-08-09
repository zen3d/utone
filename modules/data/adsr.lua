sptbl["adsr"] = {

    files = {
        module = "adsr.c",
        header = "adsr.h",
        example = "ex_adsr.c",
    },

    func = {
        create = "ut_adsr_create",
        destroy = "ut_adsr_destroy",
        init = "ut_adsr_init",
        compute = "ut_adsr_compute",
    },

    params = {
        optional = {
            {
                name = "atk",
                type = "UTFLOAT",
                description = "Attack time (in seconds)",
                default = 0.1
            },
            {
                name = "dec",
                type = "UTFLOAT",
                description ="Decay time (in seconds)",
                default = 0.1
            },
            {
                name = "sus",
                type = "UTFLOAT",
                description ="Sustain (in range 0-1)",
                default = 0.5
            },
            {
                name = "rel",
                type = "UTFLOAT",
                description ="Release time (in seconds)",
                default = 0.3
            },
        }
    },

    modtype = "module",

    description = [[ADSR generator
This is an ADSR generator whose curves are created using a one-pole low pass filter.
]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "gate",
            description = "Gate signal. This should be a steady state signal that jumps from 0 to 1."
        },
    },

    outputs = {
        {
            name = "out",
            description = "ADSR envelope."
        },
    }

}
