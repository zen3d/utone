sptbl["pluck"] = {

    files = { 
        module = "pluck.c",
        header = "pluck.h",
        example = "ex_pluck.c",
    },
    
    func = {
        create = "ut_pluck_create",
        destroy = "ut_pluck_destroy",
        init = "ut_pluck_init",
        compute = "ut_pluck_compute",
    },
    
    params = {
        mandatory = {
            {
                name = "ifreq",
                type = "UTFLOAT",
                description = "Sets the initial frequency. This frequency is used to allocate all the buffers needed for the delay. This should be the lowest frequency you plan on using.",
                default = 110
            }
        },
    
        optional = {
            {
                name = "freq",
                type = "UTFLOAT",
                description = [[Variable frequency. Values less than the initial 
frequency (ifreq) will be doubled until it is greater than or equal to ifreq.]],
                default = "ifreq"
            },
            {
                name = "amp",
                type = "UTFLOAT",
                description ="Amplitude",
                default = 0.5
            },
        }
    },
    
    modtype = "module",
    
    description = [[Karplus-Strong plucked string instrument.]], 
    
    ninputs = 1,
    noutputs = 1,
    
    inputs = { 
        {
            name = "trigger",
            description = "Trigger input. When non-zero, will reinitialize and pluck."
        },
    },
    
    outputs = {
        {
            name = "out",
            description = "Signal output."
        },
    }
}
