sptbl["pinknoise"] = {

    files = {
        module = "pinknoise.c",
        header = "pinknoise.h",
        example = "ex_pinknoise.c",
    },

    func = {
        create = "ut_pinknoise_create",
        destroy = "ut_pinknoise_destroy",
        init = "ut_pinknoise_init",
        compute = "ut_pinknoise_compute",
    },

    params = {
        optional = {
            {
                name = "amp",
                type = "UTFLOAT",
                description = "Amplitude. (Value between 0-1).",
                default = 1.0
            },
        }
    },

    modtype = "module",

    description = [[Pink pinknoise generator]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
        {
            name = "dummy",
            description = "This doesn't do anything"
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }

}
