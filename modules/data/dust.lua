sptbl["dust"] = {

    files = {
        module = "dust.c",
        header = "dust.h",
        example = "ex_dust.c",
    },

    func = {
        create = "ut_dust_create",
        destroy = "ut_dust_destroy",
        init = "ut_dust_init",
        compute = "ut_dust_compute",
    },

    params = {
        optional = {
            {
                name = "amp",
                type = "UTFLOAT",
                description = "",
                default = 0.3
            },
            {
                name = "density",
                type = "UTFLOAT",
                description = "",
                default = 10
            },
            {
                name = "bipolar",
                type = "int",
                description = "Bipolar flag. A non-zero makes the signal bipolar as opposed to unipolar. ",
                default = 0
            }
        }
    },

    modtype = "module",

    description = [[A series of random impulses]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
    },

    outputs = {
        {
            name = "out",
            description = "Signal out."
        },
    }

}
