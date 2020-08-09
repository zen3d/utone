sptbl["pshift"] = {

    files = {
        module = "pshift.c",
        header = "pshift.h",
        example = "ex_pshift.c",
    },

    func = {
        create = "ut_pshift_create",
        destroy = "ut_pshift_destroy",
        init = "ut_pshift_init",
        compute = "ut_pshift_compute",
    },

    params = {
        optional = {
            {
                name = "shift",
                type = "UTFLOAT*",
                description = "Pitch shift (in semitones), range -24/24.",
                default = 0
            },
            {
                name = "window",
                type = "UTFLOAT*",
                description ="Window size (in samples), max 10000",
                default = 1000
            },
            {
                name = "xfade",
                type = "UTFLOAT*",
                description ="Crossfade (in samples), max 10000",
                default = 10
            },
        }
    },

    modtype = "module",

    description = [[Time-domain pitch shifter.]],

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
            description = "Signal output."
        },
    }

}
