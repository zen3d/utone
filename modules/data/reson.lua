sptbl["reson"] = {

    files = { 
        module = "reson.c",
        header = "reson.h",
        example = "ex_reson.c",
    },
    
    func = {
        create = "ut_reson_create",
        destroy = "ut_reson_destroy",
        init = "ut_reson_init",
        compute = "ut_reson_compute",
    },
    
    params = {
        optional = {
            {
                name = "freq",
                type = "UTFLOAT",
                description = "Center frequency of the filter, or frequency position of the peak response.",
                default = 4000
            },
            {
                name = "bw",
                type = "UTFLOAT",
                description = "Bandwidth of the filter.",
                default = 1000
            }
        },
    
    },
    
    modtype = "module",
    
    description = [[A second-order resonant filter. NOTE: The output for reson appears to be very hot, so take caution when using this module.]], 
    
    ninputs = 1,
    noutputs = 1,
    
    inputs = { 
        {
            name = "input",
            description = "Signal Input."
        },
    },
    
    outputs = {
        {
            name = "output",
            description = "Signal output."
        },
    }

}
