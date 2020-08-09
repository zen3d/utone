sptbl["rspline"] = {

    files = {
        module = "rspline.c",
        header = "rspline.h",
        example = "ex_rspline.c",
    },

    func = {
        create = "ut_rspline_create",
        destroy = "ut_rspline_destroy",
        init = "ut_rspline_init",
        compute = "ut_rspline_compute",
    },

    params = {
        optional = {
            {
                name = "min",
                type = "UTFLOAT",
                description = "Minimum range.",
                default = 0
            },
            {
                name = "max",
                type = "UTFLOAT",
                description ="Maximum range",
                default = 1 
            },
            {
                name = "cps_min",
                type = "UTFLOAT",
                description = "",
                default = 0.1
            },
            {
                name = "cps_max",
                type = "UTFLOAT",
                description ="",
                default = 3 
            },
        }
    },

    modtype = "module",

    description = [[Random spline curve generator
This is a function that generates random spline curves. This signal generator
is ideal for control signals. Curves are quite smooth when cps_min is not
too different from cps_max. When the range of these two is big, 
some discontinuity may occur. Due to the interpolation, the output 
may be greater than the range values. 
]],

    ninputs = 0,
    noutputs = 1,

    inputs = {
        {
            name = "dummy",
            description = "Dummy input."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }

}
