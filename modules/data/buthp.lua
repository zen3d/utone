sptbl["buthp"] = {

    files = {
        module = "buthp.c",
        header = "buthp.h",
        example = "ex_buthp.c",
    },

    func = {
        create = "ut_buthp_create",
        destroy = "ut_buthp_destroy",
        init = "ut_buthp_init",
        compute = "ut_buthp_compute",
    },

    params = {
        optional = {
            {
                name = "freq",
                type = "UTFLOAT",
                description = "Cutoff Frequency.",
                default = 1000
            },
        }
    },

    modtype = "module",

    description = [[Highpass Butterworth filter]],

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
            name = "output",
            description = "Signal output."
        },
    }

}
