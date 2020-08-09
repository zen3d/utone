sptbl["sdelay"] = {

    files = {
        module = "sdelay.c",
        header = "sdelay.h",
        example = "ex_sdelay.c",
    },

    func = {
        create = "ut_sdelay_create",
        destroy = "ut_sdelay_destroy",
        init = "ut_sdelay_init",
        compute = "ut_sdelay_compute",
    },

    params = {
        mandatory = {
            {
                name = "size",
                type = "UTFLOAT",
                description = "Size of delay (in samples)",
                default = "128"
            },
        }

    },

    modtype = "module",

    description = [[Delays a signal by a number of samples.
]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "input",
            description = "Input signal to be delayed."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output for sdelay."
        },
    }

}
