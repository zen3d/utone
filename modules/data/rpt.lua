sptbl["rpt"] = {

    files = {
        module = "rpt.c",
        header = "rpt.h",
        example = "ex_rpt.c",
    },

    func = {
        create = "ut_rpt_create",
        destroy = "ut_rpt_destroy",
        init = "ut_rpt_init",
        compute = "ut_rpt_compute",
    },

    params = {
        mandatory = {
            {
                name = "maxdur",
                type = "UTFLOAT",
                description = "Maximum delay duration in seconds. This will set the buffer size.",
                default = "0.7"
            }
        },
    },

    modtype = "module",

    description = [[Trigger based beat-repeat stuttering effect

    When the input is a non-zero value, rpt will load up the buffer and loop a certain number of times. Speed and repeat amounts can be set with the ut_rpt_set function.]],

    ninputs = 2,
    noutputs = 1,

    inputs = {
        {
            name = "trig",
            description = "When this value is non-zero, it will start the repeater."
        },
        {
            name = "input",
            description = "The signal to be repeated."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal out. This is passive unless explicity triggered in the input."
        },
    }

}
