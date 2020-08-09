sptbl["butlp"] = {

    files = {
        module = "butlp.c",
        header = "butlp.h",
        example = "ex_butlp.c",
    },

    func = {
        create = "ut_butlp_create",
        destroy = "ut_butlp_destroy",
        init = "ut_butlp_init",
        compute = "ut_butlp_compute",
    },

    params = {
        optional = {
            {
                name = "freq",
                type = "UTFLOAT",
                description = "Cutoff Frequency.",
                default = 1000
            },
        }
    },

    modtype = "module",

    description = [[Lowpass Butterworth filter]],

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
