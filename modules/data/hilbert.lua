sptbl["hilbert"] = {

    files = {
        module = "hilbert.c",
        header = "hilbert.h",
        example = "ex_hilbert.c",
    },

    func = {
        create = "ut_hilbert_create",
        destroy = "ut_hilbert_destroy",
        init = "ut_hilbert_init",
        compute = "ut_hilbert_compute",
    },

    params = {
    },

    modtype = "module",

    description = [[Hilbert transform

]],

    ninputs = 1,
    noutputs = 2,

    inputs = {
        {
            name = "input",
            description = "Input signal."
        },
    },

    outputs = {
        {
            name = "out1",
            description = "Sine output."
        },
        {
            name = "out2",
            description = "Cosine output."
        },
    }

}
