sptbl["tseq"] = {

    files = {
        module = "tseq.c",
        header = "tseq.h",
        example = "ex_tseq.c",
    },

    func = {
        create = "ut_tseq_create",
        destroy = "ut_tseq_destroy",
        init = "ut_tseq_init",
        compute = "ut_tseq_compute",
    },

    params = {
        mandatory = {
            {
                name = "ft",
                type = "ut_ftbl *",
                description = "An ftable of values",
                default = "N/A"
            },
        },

        optional = {
            {
                name = "shuf",
                type = "int",
                description = "When shuf is non-zero, randomly pick a value rather than cycle through sequentially.",
                default = 0
            },
        }
    },

    modtype = "module",

    description = [[Function table looper

    TSeq runs through values in an ftable. It will change values when the trigger input is a non-zero value, and wrap around when it reaches the end.]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "trig",
            description = "Trigger."
        },
    },

    outputs = {
        {
            name = "val",
            description = "Value from current position in the ftable."
        },
    }

}
