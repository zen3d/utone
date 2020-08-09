sptbl["gen_gauss"] = {

    files = {
        module = "ftbl.c",
        header = "ftbl.h",
        example = "ex_gen_gauss.c",
    },

    func = {
        name = "ut_gen_gauss",
    },

    params = {
        {
            name = "scale",
            type = "UTFLOAT",
            description = [[The scale of the distribution, in the range of -/+scale]],
            default = 123456
        },
        {
            name = "seed",
            type = "uint32_t",
            description = [[Random seed.]],
            default = 123456
        },
    },

    modtype = "gen",

    description = [[Gaussian distribution]],

}
