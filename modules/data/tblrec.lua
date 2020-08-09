sptbl["tblrec"] = {

    files = {
        module = "tblrec.c",
        header = "tblrec.h",
        example = "ex_tblrec.c",
    },

    func = {
        create = "ut_tblrec_create",
        destroy = "ut_tblrec_destroy",
        init = "ut_tblrec_init",
        compute = "ut_tblrec_compute",
    },

    params = {
        mandatory = {
            {
                name = "bar",
                type = "ut_ftbl *",
                description = "",
                default = "N/A"
            },
        },
    },

    modtype = "module",

    description = [[Record a signal to an ftable.
This module will write audio-rate signals to a preallocated utone ftable. 
Every time record is enabled, it will got back to index 0 overwrite any
previous information that was on it. 
]],

    ninputs = 2,
    noutputs = 1,

    inputs = {
        {
            name = "in",
            description = "Input signal."
        },
        {
            name = "trig",
            description = "When non-zero, will toggle recording on/off. Recording will set the playhead back to zero"
        },
    },

    outputs = {
        {
            name = "out",
            description = "Copy of the input signal."
        }
    }

}
