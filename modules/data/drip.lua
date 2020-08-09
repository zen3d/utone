sptbl["drip"] = {

    files = {
        module = "drip.c",
        header = "drip.h",
        example = "ex_drip.c",
    },

    func = {
        create = "ut_drip_create",
        destroy = "ut_drip_destroy",
        init = "ut_drip_init",
        compute = "ut_drip_compute",
    },

    params = {
        mandatory = {
            {
                name = "dettack",
                type = "UTFLOAT",
                description = "Period of time over which all sound is stopped.",
                default = 0.09
            },
        },

        optional = {
            {
                name = "num_tubes",
                type = "UTFLOAT",
                description = "Number of units.",
                default = 10
            },
            {
                name = "amp",
                type = "UTFLOAT",
                description = "Amplitude.",
                default = 0.3
            },
            {
                name = "damp",
                type = "UTFLOAT",
                description ="The damping factor. Maximum value is 2.0.",
                default = 0.2
            },
            {
                name = "shake_max",
                type = "UTFLOAT",
                description = "The amount of energy to add back into the system.",
                default = 0
            },
            {
                name = "freq",
                type = "UTFLOAT",
                description ="Main resonant frequency.",
                default = 450
            },
            {
                name = "freq1",
                type = "UTFLOAT",
                description ="The first resonant frequency.",
                default = 600
            },
            {
                name = "freq2",
                type = "UTFLOAT",
                description ="The second resonant frequency.",
                default = 750
            },
        }
    },

    modtype = "module",

    description = [[Water drop physical model

    Physical model of the sound of dripping water. When triggered, it will produce a droplet of water.]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "trig",
            description = "Trigger value. When non-zero, it will re-init the drip and create a drip sound."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Stereo left output for drip."
        },
    }

}
