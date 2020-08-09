sptbl["fofilt"] = {

    files = {
        module = "fofilt.c",
        header = "fofilt.h",
        example = "ex_fofilt.c",
    },

    func = {
        create = "ut_fofilt_create",
        destroy = "ut_fofilt_destroy",
        init = "ut_fofilt_init",
        compute = "ut_fofilt_compute",
    },

    params = {
        optional = {
            {
                name = "freq",
                type = "UTFLOAT",
                description = "Center frequency.",
                default = 1000
            },
            {
                name = "atk",
                type = "UTFLOAT",
                description ="Impulse response attack time (in seconds).",
                default = 0.007
            },
            {
                name = "dec",
                type = "UTFLOAT",
                description ="Impulse reponse decay time (in seconds)",
                default = 0.04
            },
        }
    },

    modtype = "module",

    description = [[Formant filter
    When fed with a pulse train, it will generate a series of overlapping grains. Overlapping will occur when 1/freq < dec, but there is no upper limit on the number of overlaps. (cited from www.csounds.com/manual/html/fofilter.html)]],

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
