sptbl["tenv"] = {

    files = {
        module = "tenv.c",
        header = "tenv.h",
        example = "ex_tenv.c",
    },

    func = {
        create = "ut_tenv_create",
        destroy = "ut_tenv_destroy",
        init = "ut_tenv_init",
        compute = "ut_tenv_compute",
    },

    params = {
        optional = {
            {
                name = "atk",
                type = "UTFLOAT",
                description = "Attack time, in seconds.",
                default = 0.1
            },
            {
                name = "hold",
                type = "UTFLOAT",
                description = "Hold time, in seconds.",
                default = 0.3
            },
            {
                name = "rel",
                type = "UTFLOAT",
                description = "Release time, in seconds.",
                default = 0.2
            },
        }
    },

    modtype = "module",

    description = [[Trigger based linear AHD envelope generator]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "trig",
            description = "Trigger input. When non-zero, the envelope will (re)trigger."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output"
        },
    }

}
