sptbl["fosc"] = {

    files = {
        module = "fosc.c",
        header = "fosc.h",
        example = "ex_fosc.c",
    },

    func = {
        create = "ut_fosc_create",
        destroy = "ut_fosc_destroy",
        init = "ut_fosc_init",
        compute = "ut_fosc_compute",
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
                default = 0.4
            },
            {
                name = "car",
                type = "UTFLOAT",
                description ="Carrier frequency, expressed as a ratio number in C:M ratio. Typically an integer.",
                default = 1
            },
            {
                name = "mod",
                type = "UTFLOAT",
                description ="Modulator frequency, expressed as a ratio number in C:M ratio. Typically an integer.",
                default = 1
            },
            {
                name = "indx",
                type = "UTFLOAT",
                description ="Modulation index. Most commercial synthesizers have a range from 0-8, but there's nothing stopping you from going beyond that.",
                default = 8
            },
        }
    },

    modtype = "module",

    description = [[FM oscilator pair with linear interpolation]],

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
