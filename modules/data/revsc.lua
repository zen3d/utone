sptbl["revsc"] = {

    files = {
        module = "revsc.c",
        header = "revsc.h",
        example = "ex_revsc.c",
    },

    func = {
        create = "ut_revsc_create",
        destroy = "ut_revsc_destroy",
        init = "ut_revsc_init",
        compute = "ut_revsc_compute",
    },

    params = {
        optional = {
            {
                name = "feedback",
                type = "UTFLOAT",
                description = "Value between 0-1 that sets feedback value. The larger the value, the longer the decay.",
                default = 0.97
            },
            {
                name = "lpfreq",
                type = "UTFLOAT",
                description ="low pass cutoff frequency.",
                default = 10000
            },
        }
    },

    modtype = "module",

    description = [[ 8 FDN stereo reverb]],

    ninputs = 2,
    noutputs = 2,

    inputs = {
        {
            name = "input_1",
            description = "First input."
        },
        {
            name = "input_2",
            description = "Second input."
        },
    },

    outputs = {
        {
            name = "out_1",
            description = "Channel 1 output. Most likely for the left channel."
        },
        {
            name = "out_2",
            description = "Channel 2 output. Mose likely for the right channel."
        },
    }

}
