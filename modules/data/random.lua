sptbl["random"] = {

    files = {
        module = "random.c",
        header = "random.h",
        example = "ex_random.c",
    },

    func = {
        create = "ut_random_create",
        destroy = "ut_random_destroy",
        init = "ut_random_init",
        compute = "ut_random_compute",
    },

    params = {
        optional = {
            {
                name = "min",
                type = "UTFLOAT",
                description = "Minimum value.",
                default = -0.2
            },
            {
                name = "max",
                type = "UTFLOAT",
                description ="Maximum value.",
                default = 0.2
            },
        }
    },

    modtype = "module",

    description = [[Random values within a range]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
        {
            name = "dummmy",
            description = "This does nothing."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }

}
