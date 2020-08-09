sptbl["crossfade"] = {

    files = {
        module = "crossfade.c",
        header = "crossfade.h",
        example = "ex_crossfade.c",
    },

    func = {
        create = "ut_crossfade_create",
        destroy = "ut_crossfade_destroy",
        init = "ut_crossfade_init",
        compute = "ut_crossfade_compute",
    },

    params = {
        mandatory = {
        },

        optional = {
            {
                name = "pos",
                type = "UTFLOAT",
                description = "Crossfade position. 0 = all signal 1, 1 = all signal 2",
                default = 0.5
            },
        }
    },

    modtype = "module",

    description = [[Crossfade two signals. 
This module will perform a linear crossfade between two input signals.
]],

    ninputs = 2,
    noutputs = 1,

    inputs = {
        {
            name = "in1",
            description = "Input signal 1."
        },
        {
            name = "in2",
            description = "Input signal 2."
        },
    },

    outputs = {
        {
            name = "out",
            description = "signal output."
        },
    }

}
