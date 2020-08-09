sptbl["tgate"] = {

    files = {
        module = "tgate.c",
        header = "tgate.h",
        example = "ex_tgate.c",
    },

    func = {
        create = "ut_tgate_create",
        destroy = "ut_tgate_destroy",
        init = "ut_tgate_init",
        compute = "ut_tgate_compute",
    },

    params = {
        optional = {
            {
                name = "time",
                type = "UTFLOAT",
                description = "Duration of the gate (in seconds)",
                default = 0.5
            },
        }
    },

    modtype = "module",

    description = [[A triggerable gate.
]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "trigger",
            description = "When non-zero, will (re)trigger gate."
        },
    },

    outputs = {
        {
            name = "gate",
            description = "Gate output."
        },
    }

}
