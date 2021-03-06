sptbl["wpkorg35"] = {

    files = {
        module = "wpkorg35.c",
        header = "wpkorg35.h",
        example = "ex_wpkorg35.c",
    },

    func = {
        create = "ut_wpkorg35_create",
        destroy = "ut_wpkorg35_destroy",
        init = "ut_wpkorg35_init",
        compute = "ut_wpkorg35_compute",
    },

    params = {
        optional = {
            {
                name = "cutoff",
                type = "UTFLOAT",
                description = "Filter cutoff",
                default = 1000
            },
            {
                name = "res",
                type = "UTFLOAT",
                description ="Filter resonance (should be between 0-2)",
                default = 1.0
            },
            {
                name = "saturation",
                type = "UTFLOAT",
                description ="Filter saturation.",
                default = 0.0
            },
        }
    },

    modtype = "module",

    description = [[ Analogue model of the Korg 35 Lowpass Filter

Original port done by Will Pirkle:
http://www.willpirkle.com/Downloads/AN-5Korg35_V3.pdf

]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "input",
            description = "Audio input."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }

}
