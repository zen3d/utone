sptbl["bitcrush"] = {

    files = {
        module = "bitcrush.c",
        header = "bitcrush.h",
        example = "ex_bitcrush.c",
    },

    func = {
        create = "ut_bitcrush_create",
        destroy = "ut_bitcrush_destroy",
        init = "ut_bitcrush_init",
        compute = "ut_bitcrush_compute",
    },

    params = {
        optional = {
            {
                name = "bitdepth",
                type = "UTFLOAT",
                description = "Bit depth. Expects an integer in the range of 1-16. Fractional values will be truncated.",
                default = 8
            },
            {
                name = "srate",
                type = "UTFLOAT",
                description ="Sampling rate.",
                default = 10000
            },
        }
    },

    modtype = "module",

    description = [[Digital signal degradation

    Bitcrusher will digitally degrade a signal by altering the bitdepth and sampling-rate. ]],

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
            description = "Signal output"
        },
    }

}
