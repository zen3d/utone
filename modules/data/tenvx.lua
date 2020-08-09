sptbl["tenvx"] = {

    files = {
        module = "tenvx.c",
        header = "tenvx.h",
        example = "ex_tenvx.c",
    },

    func = {
        create = "ut_tenvx_create",
        destroy = "ut_tenvx_destroy",
        init = "ut_tenvx_init",
        compute = "ut_tenvx_compute",
    },

    params = {
        optional = {
            {
                name = "atk",
                type = "UTFLOAT",
                description = "Tau attack time, in seconds. Must be non-zero.",
                default = 0.1
            },
            {
                name = "hold",
                type = "UTFLOAT",
                description = "Hold time, in seconds. The duration of the gate signal.",
                default = 0.3
            },
            {
                name = "rel",
                type = "UTFLOAT",
                description = "Tau release time, in seconds. Must be non-zero.",
                default = 0.2
            },
        }
    },

    modtype = "module",

    description = [[Trigger based exponential AHD envelope generator.
    This envelope generator emulates the exponential behavior of analogue 
envelope generators by passing a gate signal (whose duration is specified via
the hold parameter) through a one-pole filter, whose filter coefficeints are
calculated in terms of tau.  
    ]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "trig",
            description = "Trigger input. When non-zero, the envelope will (re)trigger."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output"
        },
    }

}
