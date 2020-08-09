sptbl["dcblock"] = {

    files = {
        module = "dcblock.c",
        header = "dcblock.h",
    },

    func = {
        create = "ut_dcblock_create",
        destroy = "ut_dcblock_destroy",
        init = "ut_dcblock_init",
        compute = "ut_dcblock_compute",
    },

    params = {
    },

    modtype = "module",

    description = [[A simple DC block filter]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "in",
            description = "Signal input"
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output"
        },
    }

}
