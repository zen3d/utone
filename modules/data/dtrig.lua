sptbl["dtrig"] = {

    files = {
        module = "dtrig.c",
        header = "dtrig.h",
        example = "ex_dtrig.c",
    },

    func = {
        create = "ut_dtrig_create",
        destroy = "ut_dtrig_destroy",
        init = "ut_dtrig_init",
        compute = "ut_dtrig_compute",
    },

    params = {
        mandatory = {
            {
                name = "ft",
                type = "ut_ftbl *",
                description = "An ftable containing times in seconds.",
                default = "N/A"
            }
        },

        optional = {
            {
                name = "loop",
                type = "int",
                description = "When set to 1, dtrig will wrap around and loop again.",
                default = 0
            },
            {
                name = "delay",
                type = "UTFLOAT",
                description = "This sets a delay (in seconds) on the triggered output when it is initially triggered. This is useful for rhythmic sequences with rests in the beginnings.",
                default = 0
            },
            {
                name = "scale",
                type = "UTFLOAT",
                description = "Scales the timing signal. A scale of 1 is normal, a scale of 2 will double the duration, and a scale of 0.5 will halve it.",
                default = 0
            }
        }
    },

    modtype = "module",

    description = [[ Delta trigger

    This is able to create spaced out triggers. It is set off by a single trigger.]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "trig",
            description = "trigger input."
        },
    },

    outputs = {
        {
            name = "out",
            description = "These are the triggered outputs."
        },
    }

}
