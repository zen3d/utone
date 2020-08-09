sptbl["bltriangle"] = {

    files = {
        module = "bltriangle.c",
        header = "bltriangle.h",
        example = "ex_bltriangle.c",
    },

    func = {
        create = "ut_bltriangle_create",
        destroy = "ut_bltriangle_destroy",
        init = "ut_bltriangle_init",
        compute = "ut_bltriangle_compute",
    },

    params = {
        optional = {
            {
                name = "freq",
                type = "UTFLOAT*",
                description = "Frequency, (range 0-20000)",
                default = 440
            },
            {
                name = "amp",
                type = "UTFLOAT*",
                description ="Amplitude (range 0-1).",
		default = 1.0
            },
        }
    },

    modtype = "module",

    description = [[Bandlimited triangle oscillator
This is a bandlimited triangle oscillator ported from the "triangletooth" function from the Faust
programming language.
]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
        {
            name = "dummy",
            description = "This doesn't do anything."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }

}
