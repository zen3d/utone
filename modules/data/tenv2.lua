sptbl["tenv2"] = {

    files = {
        module = "tenv2.c",
        header = "tenv2.h",
        example = "ex_tenv2.c",
    },

    func = {
        create = "ut_tenv2_create",
        destroy = "ut_tenv2_destroy",
        init = "ut_tenv2_init",
        compute = "ut_tenv2_compute",
    },

    params = {
        optional = {
            {
                name = "atk",
                type = "UTFLOAT",
                description = "Attack time (in seconds).",
                default = 0.1
            },
            {
                name = "rel",
                type = "UTFLOAT",
                description ="Release time (in seconds).",
                default = 0.1
            },
        }
    },

    modtype = "module",

    description = [[Linear 2-stage Attack/Release envelope generator

    This envelope takes 2 triggers. When triggered once,
the envelope will rise to 1 according to the attack time. When triggered again, it will decay to 0 according to
the decay time.]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "trig",
            description = "Expects a trigger signal."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal out (a unipolar envelope)."
        },
    }

}
