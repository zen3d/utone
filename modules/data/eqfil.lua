sptbl["eqfil"] = {

    files = {
        module = "eqfil.c",
        header = "eqfil.h",
        example = "ex_eqfil.c",
    },

    func = {
        create = "ut_eqfil_create",
        destroy = "ut_eqfil_destroy",
        init = "ut_eqfil_init",
        compute = "ut_eqfil_compute",
    },

    params = {

        optional = {
            {
                name = "freq",
                type = "UTFLOAT",
                description = "The center frequency of the filter",
                default = 1000
            },
            {
                name = "bw",
                type = "UTFLOAT",
                description ="The peak/notch bandwidth in Hertz",
                default = 125
            },
            {
                name = "gain",
                type = "UTFLOAT",
                description ="The peak/notch gain",
                default = 2
            },
        }
    },

    modtype = "module",

    description = [[2nd order tunable equalization filter

    This provides a peak/notch filter for building parametric/graphic equalizers. With gain above 1, there will be a peak at the center frequency with a width dependent on bw. If gain is less than 1, a notch is formed around the center frequency (freq).
    ]],

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
            name = "output",
            description = "Signal output."
        },
    }

}
