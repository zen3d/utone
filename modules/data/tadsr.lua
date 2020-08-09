sptbl["tadsr"] = {

    files = {
        module = "tadsr.c",
        header = "tadsr.h",
        example = "ex_tadsr.c",
    },

    func = {
        create = "ut_tadsr_create",
        destroy = "ut_tadsr_destroy",
        init = "ut_tadsr_init",
        compute = "ut_tadsr_compute",
    },

    params = {
        optional = {
            {
                name = "atk",
                type = "UTFLOAT",
                description = "Attack time",
                default = 0.1
            },
            {
                name = "dec",
                type = "UTFLOAT",
                description ="Decay time",
                default = 0.1
            },
            {
                name = "sus",
                type = "UTFLOAT",
                description ="Sustain Level",
                default = 0.5
            },
            {
                name = "rel",
                type = "UTFLOAT",
                description ="release",
                default = 0.5
            },
        }
    },

    modtype = "module",

    description = [[Triggerable classic ADSR envelope]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "trig",
            description = "Expects trigger signal."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Envelope signal output."
        },
    }

}
