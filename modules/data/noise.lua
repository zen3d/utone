sptbl["noise"] = {

    files = {
        module = "noise.c",
        header = "noise.h",
        example = "ex_noise.c",
    },

    func = {
        create = "ut_noise_create",
        destroy = "ut_noise_destroy",
        init = "ut_noise_init",
        compute = "ut_noise_compute",
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

    description = [[White noise generator]],

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
