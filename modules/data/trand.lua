sptbl["trand"] = {

    files = {
        module = "trand.c",
        header = "trand.h",
        example = "ex_trand.c",
    },

    func = {
        create = "ut_trand_create",
        destroy = "ut_trand_destroy",
        init = "ut_trand_init",
        compute = "ut_trand_compute",
    },

    params = {
        optional = {
            {
                name = "min",
                type = "UTFLOAT",
                description ="Minimum value to use.",
                default = 0
            },
            {
                name = "max",
                type = "UTFLOAT",
                description ="Maximum value to use.",
                default = 1
            },
        }
    },

    modtype = "module",

    description = [[Triggered random number generator.
]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "trig",
            description = "When non-zero, will create a new random value."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }

}
