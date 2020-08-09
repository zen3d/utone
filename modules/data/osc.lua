sptbl["osc"] = {

    files = {
        module = "osc.c",
        header = "osc.h",
        example = "ex_osc.c",
    },

    func = {
        create = "ut_osc_create",
        destroy = "ut_osc_destroy",
        init = "ut_osc_init",
        compute = "ut_osc_compute",
    },

    params = {
        mandatory = {
            {
                name = "tbl",
                type = "ut_ftbl *",
                description = "Wavetable to read from. Note: the size of this table must be a power of 2.",
                default = "N/A"
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
        }
    },

    modtype = "module",

    description = [[ Table-lookup oscilator with linear interpolation]],

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
            description = "Signal output."
        },
    }

}
