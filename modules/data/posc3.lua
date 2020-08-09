sptbl["posc3"] = {

    files = {
        module = "posc3.c",
        header = "posc3.h",
        example = "ex_posc3.c",
    },

    func = {
        create = "ut_posc3_create",
        destroy = "ut_posc3_destroy",
        init = "ut_posc3_init",
        compute = "ut_posc3_compute",
    },

    params = {
        mandatory = {
            {
                name = "tbl",
                type = "ut_ftbl *",
                description = "Wavetable to read from. Note: the size of this table must be a power of 2.",
                default = "N/A"
            },
        },
        optional = {
            {
                name = "freq",
                type = "UTFLOAT",
                description = "Frequency (in Hz)",
                default = 440
            },
            {
                name = "amp",
                type = "UTFLOAT",
                description ="Amplitude (typically a value between 0 and 1).",
                default = 0.2
            },
        }
    },

    modtype = "module",

    description = [[ High-precision table-lookup posc3ilator with cubic interpolation]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
        {
            name = "dummy",
            description = "This does nothing."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal out."
        },
    }

}
