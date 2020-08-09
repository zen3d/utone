sptbl["foo"] = {

    files = {
        module = "foo.c",
        header = "foo.h",
        example = "ex_foo.c",
    },

    func = {
        create = "ut_foo_create",
        destroy = "ut_foo_destroy",
        init = "ut_foo_init",
        compute = "ut_foo_compute",
        other = {
            ut_foo_set = {
                description = "foo_set description goes here.",
                args = {
                    {
                        name = "var1",
                        type = "UTFLOAT",
                        description = "This is the first parameter",
                        default = 1.5
                    },
                    {
                        name = "var2",
                        type = "UTFLOAT",
                        description = "This is the second parameter",
                        default = 1.5
                    }
                }
            }
        }
    },

    params = {
        mandatory = {
            {
                name = "bar",
                type = "ut_ftbl *",
                description = "This is a mandatory table value. It does not have a default value, so we set it to 'N/A'. Any that does not or cannot have a default value should set this default value to 'N/A'.",
                default = "N/A"
            },
            {
                name = "bar2",
                type = "UTFLOAT",
                description = "This is a mandatory parameter. In utone, users will always need to specify this value, but a default value has been giving in case it is needed to write more complicated engines in the future.",
                default = 123
            }
        },

        optional = {
            {
                name = "blah_1",
                type = "UTFLOAT",
                description = "This is an optional parameter. These values are always set to a value by default, and can be set after the init function has been called.",
                default = 1.5
            },
            {
                name = "blah_2",
                type = "UTFLOAT",
                description ="This is yet another optional parameter...",
                default = 456.7
            },
        }
    },

    modtype = "module",

    description = [[A short title describing the module

    This is a description of the entire module.  This is not a real module. This description should be a comprehensive sumary of what this function does.

Inside the Lua table, this is expressed as a multiline string, however it does not adhere to the tradtional 80 column rule found in programming.

Write as much text as needed here...
]],

    ninputs = 2,
    noutputs = 2,

    inputs = {
        {
            name = "clock",
            description = "this is the clock source for a made up plugin."
        },
        {
            name = "input",
            description = "this is the audio input for a made up plugin."
        },
    },

    outputs = {
        {
            name = "out_left",
            description = "Stereo left output for foo."
        },
        {
            name = "out_right",
            description = "Stereo right output for foo."
        },
    }

}
