sptbl["smoothdelay"] = {

    files = {
        module = "smoothdelay.c",
        header = "smoothdelay.h",
        example = "ex_smoothdelay.c",
    },

    func = {
        create = "ut_smoothdelay_create",
        destroy = "ut_smoothdelay_destroy",
        init = "ut_smoothdelay_init",
        compute = "ut_smoothdelay_compute",
    },

    params = {
        mandatory = {
            {
                name = "maxdel",
                type = "UTFLOAT",
                description = "Maximum delay time (in seconds)",
                default = 1.0
            },
            {
                name = "interp",
                type = "uint32_t",
                description = "interpolation time (in samples)",
                default = 1024
            }
        },

        optional = {
            {
                name = "feedback",
                type = "UTFLOAT",
                description ="",
                default = 0.1
            },
            {
                name = "del",
                type = "UTFLOAT",
                description = "",
                default = 0.5
            },
        }
    },

    modtype = "module",

    description = [[Smooth variable delay line without varispeed pitch.
Smooth delay is based off the sdelay module in Faust. The smooth delay 
algorithm involves a double delay line. Any time the delay time changes, 
the delay time of buffer not heard changes, then is crossfaded to 
that buffer.
]],

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
            description = "Signal output."
        },
    }

}
