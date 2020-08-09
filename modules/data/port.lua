sptbl["port"] = {

    files = {
        module = "port.c",
        header = "port.h",
        example = "ex_port.c",
    },

    func = {
        create = "ut_port_create",
        destroy = "ut_port_destroy",
        init = "ut_port_init",
        compute = "ut_port_compute",
        other = {
            ut_port_reset = {
                description = "Resets internal buffers, snapping to input value instead of ramping to it.",
                args = {
                    {
                        name = "input",
                        type = "UTFLOAT *",
                        description = "input value to snap to.",
                        default = 0.0
                    },
                }
            }
        }
    },

    params = {
        mandatory = {
            {
                name = "htime",
                type = "UTFLOAT",
                description = "",
                default = 0.02
            },
        },
        optional = {
            {
                name = "htime",
                type = "UTFLOAT",
                description = "",
                default = 0.02
            },
        },
    },

    modtype = "module",

    description = [[ Portamento-style control signal smoothing

    Useful for smoothing out low-resolution signals and applying glissando to filters.]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "in",
            description = "Signal input."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }

}
