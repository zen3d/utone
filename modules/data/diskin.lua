sptbl["diskin"] = {

    files = {
        module = "diskin.c",
        header = "diskin.h",
        example = "ex_diskin.c",
    },

    func = {
        create = "ut_diskin_create",
        destroy = "ut_diskin_destroy",
        init = "ut_diskin_init",
        compute = "ut_diskin_compute",
    },

    params = {
        mandatory = {
            {
                name = "filename",
                type = "const char *",
                description = "Filename of the audio file.",
                default = "N/A"
            },
        },
    },

    modtype = "module",

    description = [[Read from an audio file

    Expects a 1-channel file matching the project samplerate. Diskin should be able to read any file format that libsndfile supports.]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
        {
            name = "dummy",
            description = "This doesn't do anything."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal out."
        },
    }

}
