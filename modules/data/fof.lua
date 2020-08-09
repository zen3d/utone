sptbl["fof"] = {

    files = {
        module = "fof.c",
        header = "fof.h",
        example = "ex_fof.c",
    },

    func = {
        create = "ut_fof_create",
        destroy = "ut_fof_destroy",
        init = "ut_fof_init",
        compute = "ut_fof_compute",
    },

    params = {
        mandatory = {
            {
                name = "sine",
                type = "ut_ftbl *",
                description = "ftable for sine wave.",
                default = "N/A"
            },
            {
                name = "win",
                type = "ut_ftbl *",
                description = "Ftable for envelope function (use either gen_line or gen_sinecomp)",
                default = "N/A"
            },
            {
                name = "iolaps",
                type = "int",
                description = "Maximum number of foflet overlaps.",
                default = 100 
            },
            {
                name = "iphs",
                type = "UTFLOAT",
                description = "Phase",
                default = 0
            }
        },

        optional = {
            {
                name = "amp",
                type = "UTFLOAT",
                description = "Overall amplitude",
                default = 0.5
            },
            {
                name = "fund",
                type = "UTFLOAT",
                description = "Fundamental frequency",
                default = 100
            },
            {
                name = "form",
                type = "UTFLOAT",
                description = "Formant frequency.",
                default = 500
            },
            {
                name = "oct",
                type = "UTFLOAT",
                description = "Octaviation index, if greater than zero, lowers the effective fund frequency by attenuating odd-numbered sine bursts. whole numbers are full octaves. fractions transpositional.",
                default = 0
            },
            {
                name = "band",
                type = "UTFLOAT",
                description = "Bandwidth (in -6db) expressed in Hz. The bandwidth determines the rate of exponential decay throughout the sineburst, before the enveloping is applied.",
                default = 50
            },
            {
                name = "ris",
                type = "UTFLOAT",
                description = "Rise of sinusoid burst (in seconds)",
                default = 0.003
            },
            {
                name = "dec",
                type = "UTFLOAT",
                description = "Decay of the sinusoid burst (in seconds).",
                default = 0.0007
            },
            {
                name = "dur",
                type = "UTFLOAT",
                description = "OVerall duration of sinusoid burst (in seconds).",
                default = 0.02
            },
        }
    },

    modtype = "module",

    description = [[Produces sinusoid bursts for granular and formant synthesis

]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }

}
