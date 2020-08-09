sptbl["spa"] = {

    files = {
        module = "spa.c",
        header = "spa.h",
        example = "ex_spa.c",
    },

    func = {
        create = "ut_uta_create",
        destroy = "ut_uta_destroy",
        init = "ut_uta_init",
        compute = "ut_uta_compute",
    },

    params = {
        mandatory = {
            {
                name = "filename",
                type = "const char *",
                description = "Filename of SPA file",
                default = "N/A"
            },
        },

    },

    modtype = "module",

    description = [[Stream a Soundpipe Audio File
Similar to ut_diskin, ut_uta will stream a file in the internal utone
audio format. Such a format is useful for instances where you need to read
audio files, but can't use libsndfile. 
]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
    },

    outputs = {
        {
            name = "out",
            description = "Output to spa."
        },
    }

}
