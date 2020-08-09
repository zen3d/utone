sptbl["jitter"] = {

    files = {
        module = "jitter.c",
        header = "jitter.h",
        example = "ex_jitter.c",
    },

    func = {
        create = "ut_jitter_create",
        destroy = "ut_jitter_destroy",
        init = "ut_jitter_init",
        compute = "ut_jitter_compute",
    },

    params = {
        optional = {
            {
                name = "amp",
                type = "UTFLOAT",
                description ="The amplitude of the line. Will produce values in the range of (+/-)amp.",
                default = 0.5
            },
            {
                name = "cpsMin",
                type = "UTFLOAT",
                description = "The minimum frequency of change in Hz.",
                default = 0.5
            },
            {
                name = "cpsMax",
                type = "UTFLOAT",
                description ="The maximum frequency of change in Hz.",
                default = 4
            },
        }
    },

    modtype = "module",

    description = [[A signal with random fluctuations

     This is useful for emulating jitter found in analogue equipment. ]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
        {
            name = "dummy",
            description = "This doesn't do anything."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }

}
