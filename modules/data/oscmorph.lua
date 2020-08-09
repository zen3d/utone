sptbl["oscmorph"] = {

    files = {
        module = "oscmorph.c",
        header = "oscmorph.h",
        example = "ex_oscmorph.c",
    },

    func = {
        create = "ut_oscmorph_create",
        destroy = "ut_oscmorph_destroy",
        init = "ut_oscmorph_init",
        compute = "ut_oscmorph_compute",
    },

    params = {
        mandatory = {
            {
                name = "tbl",
                type = "ut_ftbl **",
                description = "An array of ftables to read from. Note: the size of these tables must be a power of 2 (and the same size as well).",
                default = "N/A"
            },
            {
                name = "nft",
                type = "int",
                description ="Number of ftbls",
                default = 2
            },
            {
                name = "phase",
                type = "UTFLOAT",
                description ="Initial phase of waveform, expects a value 0-1",
                default = 0
            }
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
            {
                name = "wtpos",
                type = "UTFLOAT",
                description ="Wavetable position. (scaled 0-1)",
                default = 0.0
            },
        }
    },

    modtype = "module",

    description = [[Wavetable morphing oscillator

This is an oscillator with linear interpolation that is capable of morphing 
between an arbitrary number of wavetables. 
]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
        {
            name = "in",
            description = "This does nothing."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }

}
