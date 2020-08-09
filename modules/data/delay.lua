sptbl["delay"] = {

    files = {
        module = "delay.c",
        header = "delay.h",
        example = "ex_delay.c",
    },

    func = {
        create = "ut_delay_create",
        destroy = "ut_delay_destroy",
        init = "ut_delay_init",
        compute = "ut_delay_compute",
    },

    params = {
        mandatory = {
            {
                name = "time",
                type = "UTFLOAT",
                description = "Delay time, in seconds.",
                default = 1.0
            }
        },

        optional = {
            {
                name = "feedback",
                type = "UTFLOAT",
                description = "Feedback amount. Should be a value between 0-1.",
                default = 0.0
            }
        }

    },

    modtype = "module",

    description = [[Adds a delay to an incoming signal with optional feedback.]],

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
        },
    }

}
