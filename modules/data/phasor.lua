sptbl["phasor"] = {

    files = {
        module = "phasor.c",
        header = "phasor.h",
        example = "ex_phasor.c",
    },

    func = {
        create = "ut_phasor_create",
        destroy = "ut_phasor_destroy",
        init = "ut_phasor_init",
        compute = "ut_phasor_compute",
    },

    params = {
        mandatory = {
            {
                name = "iphs",
                type = "UTFLOAT",
                description = "initial phase",
                default = 0
            },
        },

        optional = {
            {
                name = "freq",
                type = "UTFLOAT",
                description = "Frequency.",
                default = 1.5
            },
        }
    },

    modtype = "module",

    description = [[Normalized sawtooth wave from 0 to 1

    Phasors are often used when building table-lookup oscillators.]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
        {
            name = "dummy",
            description = "this doesn't do anything."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }

}
