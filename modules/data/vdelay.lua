sptbl["vdelay"] = {

    files = {
        module = "vdelay.c",
        header = "vdelay.h",
        example = "ex_vdelay.c",
    },

    func = {
        create = "ut_vdelay_create",
        destroy = "ut_vdelay_destroy",
        init = "ut_vdelay_init",
        compute = "ut_vdelay_compute",
        other = {
            ut_vdelay_reset = {
                description = "Resets delay buffer and delay pointer.",
                args = {
                }
            }
        }
    },

    params = {
        mandatory = {
            {
                name = "maxdel",
                type = "UTFLOAT",
                description = "The maximum delay time, in seconds.",
                default = 1.0,
                irate = true
            },
        },

        optional = {
            {
                name = "del",
                type = "UTFLOAT",
                description = "Delay time (in seconds) that can be changed during performance. This value must not exceed the maximum delay time.",
                default = "maxdel * 0.5"
            },
            {
                name = "feedback",
                type = "UTFLOAT",
                description = "Amount of feedback in delay line. Should be in range 0-1.",
                default = "0"
            },
        }
    },

    modtype = "module",

    description = [[Delay line with cubic interpolation]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "in",
            description = "Signal input."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal out."
        },
    }

}
