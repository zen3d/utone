sptbl["randi"] = {

    files = {
        module = "randi.c",
        header = "randi.h",
        example = "ex_randi.c",
    },

    func = {
        create = "ut_randi_create",
        destroy = "ut_randi_destroy",
        init = "ut_randi_init",
        compute = "ut_randi_compute",
    },

    params = {
        optional = {
            {
                name = "min",
                type = "UTFLOAT",
                description = "Minimum value",
                default = 0
            },
            {
                name = "max",
                type = "UTFLOAT",
                description ="Maximum value",
                default = 1
            },
            {
                name = "cps",
                type = "UTFLOAT",
                description ="Frequency to change values.",
                default = 3
            },
            {
                name = "mode",
                type = "UTFLOAT",
                description = "Randi mode (not yet implemented yet.)",
                default = 0,
                irate = true
            },
        }
    },

    modtype = "module",

    description = [[Line segments between random values within a range]],

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
            description = "Signal out."
        },
    }

}
