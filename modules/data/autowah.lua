sptbl["autowah"] = {

    files = {
        module = "autowah.c",
        header = "autowah.h",
        example = "ex_autowah.c",
    },

    func = {
        create = "ut_autowah_create",
        destroy = "ut_autowah_destroy",
        init = "ut_autowah_init",
        compute = "ut_autowah_compute",
    },

    params = {
        optional = {
            {
                name = "level",
                type = "UTFLOAT*",
                description = "Overall level (between 0 and 1)",
                default = 0.1
            },
            {
                name = "wah",
                type = "UTFLOAT*",
                description ="wah amount",
                default = 0
            },
            {
                name = "mix",
                type = "UTFLOAT*",
                description ="Wet/dry amount (100 = wet, 0 = dry)",
                default = 100
            },
        }
    },

    modtype = "module",

    description = [[Automatic wah pedal
	An automatic wah effect, ported from Guitarix via Faust. 
]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "input",
            description = "Audio input"
        },
    },
    
    outputs = {
        {
            name = "output",
            description = "Audio output."
        },
    }

}
