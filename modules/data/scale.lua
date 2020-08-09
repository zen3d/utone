sptbl["scale"] = {

    files = {
        module = "scale.c",
        header = "scale.h",
        example = "ex_scale.c",
    },

    func = {
        create = "ut_scale_create",
        destroy = "ut_scale_destroy",
        init = "ut_scale_init",
        compute = "ut_scale_compute",
    },

    params = {
        optional = {
            {
                name = "min",
                type = "UTFLOAT",
                description = "Minimum value to scale to.",
                default = 0
            },
            {
                name = "max",
                type = "UTFLOAT",
                description ="Maximum value to scale to.",
                default = 1
            },
        }
    },

    modtype = "module",

    description = [[Bipolar Scale

    This module scales from unipolar [0, 1] to another range defined by min and max.
]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "in",
            description = "Signal to be scaled."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Scaled signal out"
        },
    }

}
