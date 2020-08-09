sptbl["thresh"] = {

    files = {
        module = "thresh.c",
        header = "thresh.h",
        example = "ex_thresh.c",
    },

    func = {
        create = "ut_thresh_create",
        destroy = "ut_thresh_destroy",
        init = "ut_thresh_init",
        compute = "ut_thresh_compute",
    },

    params = {
        optional = {
            {
                name = "thresh",
                type = "UTFLOAT",
                description = "Threshold level",
                default = 1.5
            },
            {
                name = "mode",
                type = "int",
                description ="Sets when to detect theshold crossings. 0 = from below. 1 = from above. 2 = from above/below",
                default = 0
            },
        }
    },

    modtype = "module",

    description = [[Trigger generator for signals that cross a given threshold. 
]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "input",
            description = "Input signal."
        },
    },

    outputs = {
        {
            name = "trig",
            description = "Produces a trigger when the input signal crosses the set threshold."
        },
    }

}
