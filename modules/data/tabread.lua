sptbl["tabread"] = {
    files = {
        module = "tabread.c",
        header = "tabread.h",
        example = "ex_tabread.c",
    },

    func = {
        create = "ut_tabread_create",
        destroy = "ut_tabread_destroy",
        init = "ut_tabread_init",
        compute = "ut_tabread_compute",
    },

    params = {
        mandatory = {
            {
                name = "ft",
                type = "ut_ftbl *",
                description = "A properly allocated table (using a function like ut_gen_file).",
                default = "N/A"
            },
            {
                name = "mode",
                type = "UTFLOAT",
                description ="1 = scaled index, 0 = unscaled index",
                default = 1.0
            },
        },

        optional = {
            {
                name = "index",
                type = "UTFLOAT",
                description ="index position, either scaled or unscaled with mode parameter",
                default = 0
            },
            {
                name = "offset",
                type = "UTFLOAT",
                description ="Offset from beginning of ftable. If the mode is scaled, then it is in range 0-1, other wise it is the index position.",
                default = 1.0
            },
            {
                name = "wrap",
                type = "UTFLOAT",
                description ="Enable wraparound. 1 = on; 0 = 0ff.",
                default = 1.0
            }
        }
    },

    modtype = "module",

    description = [[Table 
        Read through an ut_ftbl with linear interpolation.
    ]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
        {
            name = "in",
            description = "Signal in."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }
}
