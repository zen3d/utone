sptbl["gbuzz"] = {

    files = {
        module = "gbuzz.c",
        header = "gbuzz.h",
        example = "ex_gbuzz.c",
    },

    func = {
        create = "ut_gbuzz_create",
        destroy = "ut_gbuzz_destroy",
        init = "ut_gbuzz_init",
        compute = "ut_gbuzz_compute",
    },

    params = {
        mandatory = {
            {
                name = "ft",
                type = "ut_ftbl *",
                description = "Soundpipe function table used internally. This should be a sine wave.",
                default = "N/A"
            },

            {
                name = "iphs",
                type = "UTFLOAT",
                description ="Phase to start on (in the range 0-1)",
                default = 0
            },
        },

        optional = {
            {
                name = "freq",
                type = "UTFLOAT",
                description = "Frequency, in Hertz.",
                default = 440
            },
            {
                name = "amp",
                type = "UTFLOAT",
                description ="Amplitude (Typically a value between 0 and 1).",
                default = 0.4
            },
            {
                name = "nharm",
                type = "UTFLOAT",
                description ="Number of harmonics.",
                default = 4
            },
            {
                name = "lharm",
                type = "UTFLOAT",
                description ="Lowest harmonic present. This should be a whole number integer.",
                default = 0
            },
            {
                name = "mul",
                type = "UTFLOAT",
                description ="Multiplier. This determines the relative strength of each harmonic.",
                default = 0.1
            },
        }
    },

    modtype = "module",

    description = [[Series of partials from the harmonic series

    GBuzz comes from the "buzz" family of Csound opcodes, and is capable of producing a rich spectrum of harmonic content, useful for subtractive synthesis implementation.]],

    ninputs = 0,
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
