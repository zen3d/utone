sptbl["tbvcf"] = {

    files = {
        module = "tbvcf.c",
        header = "tbvcf.h",
        example = "ex_tbvcf.c",
    },

    func = {
        create = "ut_tbvcf_create",
        destroy = "ut_tbvcf_destroy",
        init = "ut_tbvcf_init",
        compute = "ut_tbvcf_compute",
    },

    params = {
        optional = {
            {
                name = "fco",
                type = "UTFLOAT",
                description = "Filter cutoff frequency",
                default = 500
            },
            {
                name = "res",
                type = "UTFLOAT",
                description ="Resonance",
                default = 0.8
            },
            {
                name = "dist",
                type = "UTFLOAT",
                description ="Distortion. Value is typically 2.0; deviation from this can cause stability issues. ",
                default = 2.0
            },
            {
                name = "asym",
                type = "UTFLOAT",
                description ="Asymmetry of resonance. Value is between 0-1",
                default = 0.5
            },
        }
    },

    modtype = "module",

    description = [[Emulation of the Roland TB-303 filter]],

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
