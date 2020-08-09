sptbl["tdiv"] = {

    files = {
        module = "tdiv.c",
        header = "tdiv.h",
        example = "ex_tdiv.c",
    },

    func = {
        create = "ut_tdiv_create",
        destroy = "ut_tdiv_destroy",
        init = "ut_tdiv_init",
    },

    params = {
        optional = {
            {
                name = "num",
                type = "UTFLOAT",
                description = "Triggers every N times.",
                default = 2
            },
            {
                name = "offset",
                type = "UTFLOAT",
                description = "Offset amoutn.",
                default = 0
            },
        }
    },

    modtype = "module",

    description = [[Trigger divider.
This module will take in a trigger signal, and output a trigger signal
every N times.

For instance, when N = 3:

in: * * * * * * * * *

out *     *     *   

]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "trigger",
            description = "Trigger. Should be a non-zero value"
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }

}
