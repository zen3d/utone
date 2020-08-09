sptbl["tseg"] = {

    files = {
        module = "tseg.c",
        header = "tseg.h",
        example = "ex_tseg.c",
    },

    func = {
        create = "ut_tseg_create",
        destroy = "ut_tseg_destroy",
        init = "ut_tseg_init",
        compute = "ut_tseg_compute",
    },

    params = {
        mandatory = {
            {
                name = "ibeg",
                type = "UTFLOAT",
                description = "Beginning value.",
                default = 0.001; 
            },
        },

        optional = {
            {
                name = "end",
                type = "UTFLOAT",
                description = "End parameter to go to.",
                default = 1.0
            },
            {
                name = "dur",
                type = "UTFLOAT",
                description = "duration to rise to (in seconds).",
                default = 1.0
            },
            {
                name = "type",
                type = "UTFLOAT",
                description ="The type of line, which determines slope of line",
                default = -1.0
            },
        }
    },

    modtype = "module",

    description = [[This module creates a series of line segments. 
]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "trig",
            description = "trigger."
        },
    },

    outputs = {
        {
            name = "out",
            description = "tseg output."
        },
    }

}
