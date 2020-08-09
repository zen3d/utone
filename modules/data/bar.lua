sptbl["bar"] = {

    files = {
        module = "bar.c",
        header = "bar.h",
        example = "ex_bar.c",
    },

    func = {
        create = "ut_bar_create",
        destroy = "ut_bar_destroy",
        init = "ut_bar_init",
        compute = "ut_bar_compute",
    },

    params = {
        mandatory = {
            {
                name = "iK",
                type = "UTFLOAT",
                description = "Dimensionless stiffness parameter",
                default = 3
            },
            {
                name = "ib",
                type = "UTFLOAT",
                description = "High-frequency loss parameter. Keep this small",
                default = 0.001
            }
        },

        optional = {
            {
                name = "bcL",
                type = "UTFLOAT",
                description = "Boundary condition at left end of bar. 1 = clamped, 2 = pivoting, 3 = free",
                default = 1
            },
            {
                name = "bcR",
                type = "UTFLOAT",
                description = "Boundary condition at right end of bar. 1 = clamped, 2 = pivoting, 3 = free",
                default = 1
            },
            {
                name = "T30",
                type = "UTFLOAT",
                description ="30db decay time (in seconds).",
                default = 3
            },
            {
                name = "scan",
                type = "UTFLOAT",
                description ="Speed of scanning the output location.",
                default = 0.25
            },
            {
                name = "pos",
                type = "UTFLOAT",
                description ="Position along bar that strike occurs.",
                default = 0.2
            },
            {
                name = "vel",
                type = "UTFLOAT",
                description ="Normalized strike velocity",
                default = 500
            },
            {
                name = "wid",
                type = "UTFLOAT",
                description ="Spatial width of strike.",
                default = 0.05
            },
        }
    },

    modtype = "module",

    description = [[Physical model approximating the sound of a struck metal bar]],

    ninputs = 1,
    noutputs = 1,

    inputs = {
        {
            name = "trig",
            description = "Non-zero values will strike the bar."
        },
    },

    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }

}
