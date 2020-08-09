sptbl["samphold"] = {

    files = {
        module = "samphold.c",
        header = "samphold.h",
        example = "ex_samphold.c",
    },

    func = {
        create = "ut_samphold_create",
        destroy = "ut_samphold_destroy",
        init = "ut_samphold_init",
        compute = "ut_samphold_compute",
    },

    params = {
    },

    modtype = "module",

    description = [[Classic sample and hold]],

    ninputs = 2,
    noutputs = 1,

    inputs = {
        {
            name = "trig",
            description = "Will hold the current input value when non-zero."
        },
        {
            name = "input",
            description = "Audio input."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        }
    }

}
