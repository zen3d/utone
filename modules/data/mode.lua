sptbl["mode"] = {

    files = {
        module = "mode.c",
        header = "mode.h",
        example = "ex_mode.c",
    },

    func = {
        create = "ut_mode_create",
        destroy = "ut_mode_destroy",
        init = "ut_mode_init",
        compute = "ut_mode_compute",
    },

    params = {
        optional = {
            {
                name = "freq",
                type = "UTFLOAT",
                description = "Resonant frequency of the filter.",
                default = 500
            },
            {
                name = "q",
                type = "UTFLOAT",
                description ="Quality factor of the filter. Roughly equal to q/freq.",
                default = 50
            },
        }
    },

    modtype = "module",

    description = [[Resonance filter used for modal synthesis

    Plucked and bell sounds can be created by passing an impulse through a combination of modal filters. ]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "in",
            description = "Signal input."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }

}
