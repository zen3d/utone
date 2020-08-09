sptbl["clock"] = {

    files = {
        module = "clock.c",
        header = "clock.h",
        example = "ex_clock.c",
    },

    func = {
        create = "ut_clock_create",
        destroy = "ut_clock_destroy",
        init = "ut_clock_init",
        compute = "ut_clock_compute",
    },

    params = {

        optional = {
            {
                name = "bpm",
                type = "UTFLOAT",
                description = "Clock tempo, in beats per minute.",
                default = 120
            },
            {
                name = "subdiv",
                type = "UTFLOAT",
                description ="Clock subdivision. 2 = eighths, 4 = 16ths, etc.",
                default = 1
            },
        }
    },

    modtype = "module",

    description = [[Resettable clock with subdivisions
]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "trig",
            description = "When non-zero, will reset clock"
        },
    },

    outputs = {
        {
            name = "out",
            description = "Clock output."
        },
    }

}
