sptbl["butbr"] = {

    files = {
        module = "butbr.c",
        header = "butbr.h",
        example = "ex_butbr.c",
    },

    func = {
        create = "ut_butbr_create",
        destroy = "ut_butbr_destroy",
        init = "ut_butbr_init",
        compute = "ut_butbr_compute",
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
                default = 1000
            },
        }
    },

    modtype = "module",

    description = [[Band-reject Butterworth filter]],

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
