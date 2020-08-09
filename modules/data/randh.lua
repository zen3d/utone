sptbl["randh"] = {

    files = {
        module = "randh.c",
        header = "randh.h",
        example = "ex_randh.c",
    },

    func = {
        create = "ut_randh_create",
        destroy = "ut_randh_destroy",
        init = "ut_randh_init",
        compute = "ut_randh_compute",
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
            {
                name = "freq",
                type = "UTFLOAT",
                description = "Frequency of randomization (in Hz)",
                default = 10
            },
        }
    },

    modtype = "module",

    description = [[Random number generator with hold time.
Randh is loosely based off of the Csound opcode randomh. The design is equivalent
to scaled noise sent through a classic sample and hold module.
]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }

}
