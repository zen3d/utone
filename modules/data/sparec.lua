sptbl["utarec"] = {

    files = {
        module = "utarec.c",
        header = "utarec.h",
        example = "ex_utarec.c",
    },

    func = {
        create = "ut_utarec_create",
        destroy = "ut_utarec_destroy",
        init = "ut_utarec_init",
        compute = "ut_utarec_compute",
        other = {
            ut_utarec_close = {
                description = "Close spa file and writes the rest of the data in the buffer.",
                args = {
                }
            }
        }
    },

    params = {
        mandatory = {
            {
                name = "filename",
                type = "const char *",
                description = "Filename to write to",
                default = "N/A"
            },
        },

    },

    modtype = "module",

    description = [[Writes signal to spa file.]],

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
            name = "out",
            description = "Copy of input signal."
        }
    }

}
