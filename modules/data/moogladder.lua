sptbl["moogladder"] = {

    files = {
        module = "moogladder.c",
        header = "moogladder.h",
        example = "ex_moogladder.c",
    },

    func = {
        create = "ut_moogladder_create",
        destroy = "ut_moogladder_destroy",
        init = "ut_moogladder_init",
        compute = "ut_moogladder_compute",
    },

    params = {
        optional = {
            {
                name = "freq",
                type = "UTFLOAT",
                description = "Filter cutoff frequency.",
                default = 1000
            },
            {
                name = "res",
                type = "UTFLOAT",
                description ="Filter resonance",
                default = 0.4
            },
        }
    },

    modtype = "module",

    description = [[Low pass resonant filter based on the Moogladder filter]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        { name = "input",
            description = "The clock source for a made-up plugin."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Stereo left output for moogladder."
        },
    }

}
