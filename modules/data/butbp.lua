sptbl["butbp"] = {

    files = {
        module = "butbp.c",
        header = "butbp.h",
        example = "ex_butbp.c",
    },

    func = {
        create = "ut_butbp_create",
        destroy = "ut_butbp_destroy",
        init = "ut_butbp_init",
        compute = "ut_butbp_compute",
    },

    params = {
        optional = {
            {
                name = "freq",
                type = "UTFLOAT",
                description = "Center Frequency. (in Hertz)",
                default = 1000
            },
            {
                name = "bw",
                type = "UTFLOAT",
                description = "Bandwidth. (in Hertz)",
                default = 10
            },
        }
    },

    modtype = "module",

    description = [[Bandpass Butterworth filter]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "input",
            description = "Input signal that the filter should be applied to."
        },
    },

    outputs = {
        {
            name = "output",
            description = "Output signal (input modified by the filter)."
        },
    }

}
