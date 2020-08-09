sptbl["conv"] = {

    files = {
        module = "conv.c",
        header = "conv.h",
        example = "ex_conv.c",
    },

    func = {
        create = "ut_conv_create",
        destroy = "ut_conv_destroy",
        init = "ut_conv_init",
        compute = "ut_conv_compute",
    },

    params = {
        mandatory = {
            {
                name = "ft",
                type = "ut_ftbl *",
                description = "Ftable used as the impulse response. ",
                default = "N/A"
            },
            {
                name = "iPartLen",
                type = "UTFLOAT",
                description = [[Partition length (in samples). 
Must be a power of 2. Lower values will add less latency, at the cost 
of requiring more CPU power. 
]],
                default = 2048
            }
        },

    },

    modtype = "module",

    description = [[Partioned convolution. 
This module will perform partitioned convolution on an input signal using
an ftable as an impulse response.]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "input",
            description = "Signal input to be convolved."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }

}
