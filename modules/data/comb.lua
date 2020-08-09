sptbl["comb"] = {

    files = {
        module = "comb.c",
        header = "comb.h",
        example = "ex_comb.c",
    },

    func = {
        create = "ut_comb_create",
        destroy = "ut_comb_destroy",
        init = "ut_comb_init",
        compute = "ut_comb_compute",
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
                description = "Reverberation time, in seconds (RT-60).",
                default = 3.5
            },
        }
    },

    modtype = "module",

    description = [[Comb filter]],

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
