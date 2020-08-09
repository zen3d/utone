sptbl["blsquare"] = {

    files = {
        module = "blsquare.c",
        header = "blsquare.h",
        example = "ex_blsquare.c",
    },

    func = {
        create = "ut_blsquare_create",
        destroy = "ut_blsquare_destroy",
        init = "ut_blsquare_init",
        compute = "ut_blsquare_compute",
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
            {
                name = "width",
                type = "UTFLOAT*",
                description ="Duty cycle width (range 0-1).",
		default = 0.5
            },
        }
    },

    modtype = "module",

    description = [[Bandlimited square oscillator
This is a bandlimited square oscillator ported from the "squaretooth" function from the Faust
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
