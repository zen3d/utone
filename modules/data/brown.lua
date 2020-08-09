sptbl["brown"] = {

    files = {
        module = "brown.c",
        header = "brown.h",
        example = "ex_brown.c",
    },

    func = {
        create = "ut_brown_create",
        destroy = "ut_brown_destroy",
        init = "ut_brown_init",
        compute = "ut_brown_compute",
    },

    params = {
    },

    modtype = "module",

    description = [[Brownian noise generator.
]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
    },

    outputs = {
        {
            name = "out",
            description = "Brownian noise output."
        },
    }

}
