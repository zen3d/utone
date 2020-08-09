sptbl["dist"] = {

    files = {
        module = "dist.c",
        header = "dist.h",
        example = "ex_dist.c",
    },

    func = {
        create = "ut_dist_create",
        destroy = "ut_dist_destroy",
        init = "ut_dist_init",
        compute = "ut_dist_compute",
    },

    params = {
        optional = {
            {
                name = "pregain",
                type = "UTFLOAT",
                description ="Gain applied before waveshaping.",
                default = 2.0
            },
            {
                name = "postgain",
                type = "UTFLOAT",
                description ="Gain applied after waveshaping",
                default = 0.5
            },
            {
                name = "shape1",
                type = "UTFLOAT",
                description ="Shape of the positive part of the signal. A value of 0 gets a flat clip.",
                default = 0
            },
            {
                name = "shape2",
                type = "UTFLOAT",
                description ="Like shape1, only for the negative part of the signal.",
                default = 0
            },

        }
    },

    modtype = "module",

    description = [[Distortion using a modified hyperbolic tangent function]],

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
        }
    }

}
