sptbl["allpass"] = {

    files = {
        module = "allpass.c",
        header = "allpass.h",
        example = "ex_allpass.c",
    },

    func = {
        create = "ut_allpass_create",
        destroy = "ut_allpass_destroy",
        init = "ut_allpass_init",
        compute = "ut_allpass_compute",
    },

    params = {
        mandatory = {
            {
                name = "looptime",
                type = "UTFLOAT",
                description = "The loop time of the filter, in seconds. This can also be thought of as the delay time.",
                default = 0.1
            }
        },

        optional = {
            {
                name = "revtime",
                type = "UTFLOAT",
                description = "The reverberation time, in seconds (RT-60).",
                default = 3.5
            },
        }
    },

    modtype = "module",

    description = [[Allpass filter

    Often used for the creation of reverb modules.]],

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
