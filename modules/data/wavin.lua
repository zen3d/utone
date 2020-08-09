sptbl["wavin"] = {

    files = {
        module = "wavin.c",
        header = "wavin.h",
        example = "ex_wavin.c",
    },

    func = {
        create = "ut_wavin_create",
        destroy = "ut_wavin_destroy",
        init = "ut_wavin_init",
        compute = "ut_wavin_compute",
    },

    params = {
        mandatory = {
            {
                name = "filename",
                type = "const char *",
                description = "Filename",
                default = "N/A"
            },
        },

    },

    modtype = "module",

    description = [[Reads a mono WAV file.

This module reads a mono WAV file from disk. It uses the public-domain 
dr_wav library for decoding, so it can be a good substitute for libsndfile.
]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
    },

    outputs = {
        {
            name = "out",
            description = "output signal."
        },
    }

}
