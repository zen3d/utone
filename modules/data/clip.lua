sptbl["clip"] = {

    files = {
        module = "clip.c",
        header = "clip.h",
        example = "ex_clip.c",
    },

    func = {
        create = "ut_clip_create",
        destroy = "ut_clip_destroy",
        init = "ut_clip_init",
        compute = "ut_clip_compute",
    },

    params = {
        optional = {
            {
                name = "lim",
                type = "UTFLOAT",
                description = "threshold / limiting value.",
                default = 1.0
            },
        }
    },

    modtype = "module",

    description = [[Applies clip-limiting to a signal]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "in",
            description = "Input signal."
        }
    },

    outputs = {
        {
            name = "out",
            description = "Output signal."
        }
    }

}
